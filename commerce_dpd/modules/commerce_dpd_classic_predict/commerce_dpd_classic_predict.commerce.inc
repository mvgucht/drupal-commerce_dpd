<?php

/**
 * @file
 * Implementations of Commerce Hooks
 */

/**
 * Implements hook_commerce_dpd_settings_info().
 */
function commerce_dpd_classic_predict_commerce_dpd_settings_info() {
  $countries = commerce_dpd_country_get_list();
  $default_countries = commerce_dpd_ship_from_defaults();

  return array(
    'ship_from_classic_predict' => array(
      'default' => $countries,
    ),
    'ship_to_classic_predict' => array(
      'default' => $default_countries,
    ),
  );
}


/**
 * Implements hook_commerce_shipping_method_info().
 */
function commerce_dpd_classic_predict_commerce_shipping_method_info() {
  return array(
    'dpd_classic_predict' => array(
      'title' => t('DPD Classic Predict'),
      'description' => t('Lets you create DPD Classic Predict services.'),
    ),
  );
}

/**
 * Implements hook_commerce_shipping_service_info()
 */
function commerce_dpd_classic_predict_commerce_shipping_service_info() {
  $services = array();

  // Look for services currently defined in the database.
  $result = db_query('SELECT * FROM {commerce_dpd_classic_predict_service}')->fetchAllAssoc('name', PDO::FETCH_ASSOC);

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

      $price_component_type = 'dpd_classic_predict_' . $name;

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
        'shipping_method' => 'dpd_classic_predict',
        'rules_component' => !empty($service['rules_component']),
        'price_component' => $price_component_type,
        'callbacks' => array(
          'rate' => 'commerce_dpd_classic_predict_service_rate_order',
          'details_form' => 'commerce_dpd_classic_predict_service_details_form',
          'details_form_validate' => 'commerce_dpd_classic_predict_service_details_form_validate',
          'details_form_submit' => 'commerce_dpd_classic_predict_service_details_form_submit',
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
function commerce_dpd_classic_predict_service_rate_order($shipping_service, $order) {
  if (commerce_dpd_classic_predict_method_rate_access($shipping_service, $order)) {
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
function commerce_dpd_classic_predict_method_rate_access($shipping_service, $order) {
  // extract recipient address from order
  $address = commerce_dpd_order_addressfield($order);

  // DENY if there is not a country set
  if (empty($address) || empty($address['country'])) {
    return TRUE;
  }

  // DENY if address is restricted by the dpd settings
  if (!commerce_dpd_classic_predict_can_ship_to_country($address['country'])) {
    return FALSE;
  }

  // ALLOW by default
  return TRUE;

}

/**
 * Shipping service Details Form callback
 */
function commerce_dpd_classic_predict_service_details_form($pane_form, $pane_values, $checkout_pane, $order, $shipping_service) {

}

/**
 * Shipping service Details Form Validate callback
 */
function commerce_dpd_classic_predict_service_details_form_validate($details_form, $details_values, $shipping_service, $order, $form_parents) {

}

/**
 * Shipping service Details Form Submit callback
 */
function commerce_dpd_classic_predict_service_details_form_submit($details_form, $details_values, $line_item) {
}