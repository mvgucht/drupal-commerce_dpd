<?php

/**
 * @file
 * Implementations of Commerce Hooks
 */


/**
 * Implements hook_commerce_dpd_settings_info().
 */
function commerce_dpd_shop_delivery_commerce_dpd_settings_info() {
  $countries = commerce_dpd_country_get_list();
  $default_countries = commerce_dpd_ship_from_defaults();


  return array(
    'ship_from_shop_delivery' => array(
      'default' => $countries,
    ),
    'ship_to_shop_delivery' => array(
      'default' => $default_countries,
    ),
    'max_return' => array(
      'default' => '10',
    ),
    'map_height' => array(
      'default' => '400',
    ),
    'map_type' => array(
      'default' => '',
    ),
  );
}

/**
 * Implements hook_commerce_shipping_method_info().
 */
function commerce_dpd_shop_delivery_commerce_shipping_method_info() {
  return array(
    'dpd_shop_delivery' => array(
      'title' => t('DPD Shop Delivery'),
      'description' => t('Lets you create DPD Shop Delivery services.'),
    ),
  );
}

/**
 * Implements hook_commerce_shipping_service_info().
 */
function commerce_dpd_shop_delivery_commerce_shipping_service_info() {
  $services = array();

  // Look for services currently defined in the database.
  $result = db_query('SELECT * FROM {commerce_dpd_shop_delivery_service}')->fetchAllAssoc('name', PDO::FETCH_ASSOC);

  if (!empty($result)) {
    foreach ($result as $name => $service) {
      // Create a base rate price array for the service
      $base_rate = array(
        'amount' => $service['amount'],
        'currency_code' => $service['currency_code'],
        'data' => array(),
      );

      // Unserialize the data array for the service.
      $data = !empty($service['data']) ? unserialize($service['data']) : array();

      $price_component_type = 'dpd_shop_delivery_' . $name;

      // If the data array specifies an included tax, include it now.
      if (!empty($data['include_tax']) && $tax_rate = commerce_tax_rate_load($data['include_tax'])) {
        // Reverse apply the tax.
        $tax_amount = $base_rate['amount'] - ($base_rate['amount'] / (1 + $tax_rate['rate']));
        $tax_amount = commerce_tax_rate_round_amount($tax_rate, $tax_amount);

        // Add a base price to the data array.
        $component = array(
          'amount' => $base_rate['amount'] - $tax_amount,
          'currency_code' => $base_rate['currency_code'],
          'data' => array(),
        );

        $base_rate['data'] = commerce_price_component_add($base_rate, $price_component_type, $component, TRUE, FALSE);

        // Add the tax to the data array.
        $component['amount'] = $tax_amount;
        $component['data']['tax_rate'] = $tax_rate;

        $base_rate['data'] = commerce_price_component_add($base_rate, $tax_rate['price_component'], $component, TRUE);
      }

      // Add the full service array to our return value.
      $services[$name] = array(
        'title' => $service['title'],
        'display_title' => !empty($service['display_title']) ? $service['display_title'] : $service['title'],
        'description' => $service['description'],
        'shipping_method' => 'dpd_shop_delivery',
        'rules_component' => !empty($service['rules_component']),
        'price_component' => $price_component_type,
        'callbacks' => array(
          'rate' => 'commerce_dpd_shop_delivery_service_rate_order',
          'details_form' => 'commerce_dpd_shop_delivery_service_details_form',
          'details_form_validate' => 'commerce_dpd_shop_delivery_service_details_form_validate',
          'details_form_submit' => 'commerce_dpd_shop_delivery_service_details_form_submit',
        ),
        'base_rate' => $base_rate,
        'data' => $data,
      );
    }
  }

  return $services;
}

/**
 * Shipping service Rate callback
 *
 * @param object $shipping_service
 *   The shipping service object
 * @param object $order
 *   The Commerce Order Object
 * @return string or boolean
 *  The base rate for a service or FALSE if not available.
 */
function commerce_dpd_shop_delivery_service_rate_order($shipping_service, $order) {
  if (commerce_dpd_shop_delivery_method_rate_access($shipping_service, $order)) {
    return $shipping_service['base_rate'];
  }

  return FALSE;
}

/**
 * Shipping method rate access check
 *
 * Common rate checks for all dpd services
 * - Ensure address
 * - Restrict services based on enabled countries
 * - Check if order is shippable
 *
 * @param object $shipping_service
 *  Object of the shipping service
 * @param object $order
 *  The fully loaded Commerce Order Object
 *
 * @return string or boolean
 *  The TRUE if service is allowed or FALSE if not available.
 */
function commerce_dpd_shop_delivery_method_rate_access($shipping_service, $order) {
  // extract recipient address from order
  $address = commerce_dpd_order_addressfield($order);

  // DENY if there is not a country set
  if (empty($address) || empty($address['country'])) {
    return TRUE;
  }

  // DENY if address is restricted by the dpd settings
  if (!commerce_dpd_shop_delivery_can_ship_to_country($address['country'])) {
    return FALSE;
  }

  // ALLOW by default
  return TRUE;

}

/**
 * Implements Drupal Commerce Shipping Service Details Form Callback
 */
function commerce_dpd_shop_delivery_service_details_form($pane_form, $pane_values, $checkout_pane, $order, $shipping_service) {
  // Order wrapper.
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);

  $details_form = array();
  $details_values = !empty($pane_values['service_details']) ? $pane_values['service_details'] : array();
  $dpd_shop_options = array();

  // Build the shops map markup.
  $map_markup = commerce_dpd_shop_delivery_request_map($order, $shipping_service, FALSE);

  if (empty($map_markup)) {

    drupal_set_message(t('There were no shops found for this address. Please go back and correct the address.'), 'error');
    $no_shops_markup = '<h4>' . t('No Shops Found for the address.') . '</h4>';
    $no_shops_markup .= t('Without a shop selected you can not continue with the shipping.');
    $form['dpd_no_shop'] = array(
      '#prefix' => '<div class="clearfix dpd-shop-map">',
      '#suffix' => '</div>',
      '#markup' => $no_shops_markup,
    );
    return $form;
  }


  // determine default point
  $dpd_shop_select_default = NULL;

  if (isset($details_values['shop_lon'])) {

    $details_form['shop_lon'] = array(
      '#type' => 'hidden',
      '#value' => $details_values['shop_lon'],
    );
  }

  if (isset($details_values['shop_lat'])) {

    $details_form['shop_lat'] = array(
      '#type' => 'hidden',
      '#value' => $details_values['shop_lat'],
    );
  }

  if (isset($details_values['shop_id'])) {
    $details_form['shop_id'] = array(
      '#type' => 'hidden',
      '#value' => $details_values['shop_id'],
    );
  }

  // render selected shop
  if (isset($details_values['shop_lon']) && isset($details_values['shop_lat'])) {
    $shop_lon = $details_values['shop_lon'];
    $shop_lat = $details_values['shop_lat'];
    $shop_id = $details_values['shop_id'];
    $dpd_shop_select_default = $shop_id;
  }
  else {
    $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
    //dpm($order_wrapper->getPropertyInfo(),'test');
    $dpd_shop = $order_wrapper->dpd_shop->value();
    if ($dpd_shop) {
      $shop_lon = $dpd_shop->shop_lon;
      $shop_lat = $dpd_shop->shop_lat;
      $shop_id = $dpd_shop->shop_id;
      $dpd_shop_select_default = $shop_id;
    }
  }

  if (isset($shop_lon) && isset($shop_lat)) {

    $dpd_selected_shop_details = commerce_dpd_rest_api_get_shops_by_geodata(
      $shop_lon,
      $shop_lat,
      1);
  }

  if (isset($shop_id)) {
    // theme shop details
    $dpd_shop_options[$shop_id] = theme('commerce_dpd_shop_delivery_shop_details', array(
      'shop_details' => $dpd_selected_shop_details[0]
    ));
  }

  $details_form['dpd_shop_select'] = array(
    '#type' => 'radios',
    '#default_value' => $dpd_shop_select_default,
    '#options' => $dpd_shop_options,
    '#attributes' => array('class' => array('commerce-dpd-shop-delivery-shop-option ajax-disabled clearfix')),
    '#weight' => 0,
  );
  /*
  $details_form['map_toggle'] = array(
    '#type' => 'button',
    '#value' => t('Show Map'),
    '#weight' => 2,
    '#attributes' => array('class' => array('commerce-dpd-map-toggle')),
  );
  */


  $details_form['#attached']['js'] = array(
    drupal_get_path('module', 'commerce_dpd_shop_delivery') . '/theme/commerce_dpd_shop_delivery.js',
  );


  $details_form['#attached']['css'] = array(
    drupal_get_path('module', 'commerce_dpd_shop_delivery') . '/theme/commerce_dpd_shop_delivery.css',
  );

  $details_form['#attributes']['class'][] = 'commerce-dpd-shop-delivery-service-details-form';


  return $details_form;

}

/**
 * Shipping service Details Form Validate callback
 */
function commerce_dpd_shop_delivery_service_details_form_validate($details_form, $details_values, $shipping_service, $order, $form_parents) {

  if (empty($details_values['dpd_shop_select'])) {
    drupal_set_message(t('Please select a DPD Shop where you will collect your order.'), 'error');
    return FALSE;
  }

}

/**
 * Shipping service Details Form Submit callback
 */
function commerce_dpd_shop_delivery_service_details_form_submit($details_form, $details_values, $line_item) {
  //dpm($details_values);
}

/**
 * Implements hook_commerce_checkout_pane_info()
 */
function commerce_dpd_shop_delivery_commerce_checkout_pane_info() {
  $checkout_panes = array();

  $checkout_panes['commerce_dpd_shop_delivery_order_shop_pane'] = array(
    'title' => t('DPD Shop Selected'),
    'file' => 'includes/commerce_dpd_shop_delivery.checkout_pane.inc',
    'page' => 'review',
    'weight' => 8,
  );

  return $checkout_panes;
}
