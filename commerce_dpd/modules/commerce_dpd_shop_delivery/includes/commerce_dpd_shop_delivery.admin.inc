<?php

/**
 * @file
 * Contains the administrative page and form callbacks for the dpd shop finder module.
 */

/**
 * Shipping method settings form for
 * shipping method classic_predict
 */
function commerce_dpd_shop_delivery_settings_form($form, &$form_state) {

  $countries = commerce_dpd_country_get_list();
  $default_countries = commerce_dpd_ship_from_defaults();

  $default_values = commerce_dpd_settings(array());

  // initialize vertical tab groups
  $form['groups'] = array('#type' => 'vertical_tabs');

  $form['commerce_dpd_shop_delivery_country_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Country Settings'),
    '#collapsible' => TRUE,
    '#group' => 'groups',
    '#weight' => 0,
  );

  $form['commerce_dpd_shop_delivery_map_presentation'] = array(
    '#type' => 'fieldset',
    '#title' => t('Map Presentation'),
    '#collapsible' => TRUE,
    '#group' => 'groups',
    '#weight' => 1,
  );

  $form['commerce_dpd_shop_delivery_country_settings']['ship_from_shop_delivery'] = array(
    '#type' => 'select',
    '#title' => t('Ship from'),
    '#weight' => 0,
    '#default_value' => isset($default_values['ship_from_shop_delivery']) ? $default_values['ship_from_shop_delivery'] : NULL,
    '#description' => t('Choose the location where you wish to ship your goods from.'),
    '#options' => $countries,
  );

  $form['commerce_dpd_shop_delivery_country_settings']['ship_to_shop_delivery'] = array(
    '#type' => 'select',
    '#options' => $countries,
    '#title' => t('Ship to'),
    '#weight' => 1,
    '#multiple' => TRUE,
    '#size' => 20,
    '#default_value' => isset($default_values['ship_to_shop_delivery']) ? $default_values['ship_to_shop_delivery'] : $default_countries,
    '#description' => t('Choose the DPD supported countries for delivery.'),
  );

  $form['commerce_dpd_shop_delivery_map_presentation']['map_type'] = array(
    '#type' => 'select',
    '#title' => t('Map Type'),
    '#weight' => 1,
    '#default_value' => isset($default_values['map_type']) ? $default_values['map_type'] : '1',
    '#description' => t('What kind of map do you want to show.'),
    '#options' => _commerce_dpd_shop_delivery_map_type_otions(),
  );

  $form['commerce_dpd_shop_delivery_map_presentation']['map_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Map Height'),
    '#weight' => 4,
    '#default_value' => isset($default_values['map_height']) ? $default_values['map_height'] : '400',
    '#description' => t('The height of the map in pixel.'),
  );

  $form['commerce_dpd_shop_delivery_map_presentation']['max_return'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum Return Values'),
    '#weight' => 6,
    '#default_value' => isset($default_values['max_return']) ? $default_values['max_return'] : '30',
    '#description' => t('The maximum number of returned shops'),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;

}

/**
 * Validate callback for commerce_dpd_shop_finder_settings_form()
 */
function commerce_dpd_shop_delivery_settings_form_validate($form, &$form_state) {
  $values = &$form_state['values'];
  if (empty($values['ship_to_shop_delivery'])) {
    form_set_error('ship_to_shop_delivery', t('You have to select at least one country!'));
  }
}

/**
 * Submit callback for commerce_dpd_shop_finder_settings_form()
 */
function commerce_dpd_shop_delivery_settings_form_submit($form, &$form_state) {
  form_state_values_clean($form_state);
  $values = &$form_state['values'];

  // get all current stored settings
  $current_settings = commerce_dpd_settings(array());


  // Save settings values
  // remove any values not in settings info
  $settings = array_intersect_key($values, $current_settings);

  // merge stored settings
  $settings += $current_settings;

  // save new merged settings
  variable_set('commerce_dpd_settings', $settings);

  drupal_set_message(t('The configuration options have been saved.'));

}

// -----------------------------------------------------------------------
// Rate Service Form

/**
 * Builds the form for adding and editing services.
 */
function commerce_dpd_shop_delivery_service_form($form, &$form_state, $shipping_service) {
  // Store the initial shipping service in the form state.
  $form_state['shipping_service'] = $shipping_service;

  $form['dpd_shop_delivery'] = array(
    '#tree' => TRUE,
  );

  $form['dpd_shop_delivery']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => $shipping_service['title'],
    '#description' => t('The administrative title of this DPD Shop Delivery rate. It is recommended that this title begin with a capital letter and contain only letters, numbers, and spaces.'),
    '#required' => TRUE,
    '#size' => 32,
    '#maxlength' => 255,
    '#field_suffix' => ' <small id="edit-dpd-shop-delivery-title-suffix">' . t('Machine name: @name', array('@name' => $shipping_service['name'])) . '</small>',
  );

  if (empty($shipping_service['name'])) {
    $form['dpd_shop_delivery']['name'] = array(
      '#type' => 'machine_name',
      '#title' => t('Machine name'),
      '#default_value' => $shipping_service['name'],
      '#maxlength' => 32,
      '#required' => TRUE,
      '#machine_name' => array(
        'exists' => 'commerce_shipping_service_load',
        'source' => array('dpd_shop_delivery', 'title'),
      ),
      '#description' => t('The machine-name of this DPD Shop Delivery rate. This name must contain only lowercase letters, numbers, and underscores. It must be unique.'),
    );
  }
  else {
    $form['dpd_shop_delivery']['name'] = array(
      '#type' => 'value',
      '#value' => $shipping_service['name'],
    );
  }

  $form['dpd_shop_delivery']['display_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Display title'),
    '#default_value' => $shipping_service['display_title'],
    '#description' => t('The front end display title of this DPD Shop Delivery rate shown to customers. Leave blank to default to the <em>Title</em> from above.'),
    '#size' => 32,
  );

  $form['dpd_shop_delivery']['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#description' => t('Describe this dpd rate if necessary. The text will be displayed in the dpd rate services overview table.'),
    '#default_value' => $shipping_service['description'],
    '#rows' => 3,
  );

  $form['dpd_shop_delivery']['amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Base rate'),
    '#default_value' => commerce_currency_amount_to_decimal($shipping_service['base_rate']['amount'], $shipping_service['base_rate']['currency_code']),
    '#required' => TRUE,
    '#size' => 10,
    '#prefix' => '<div class="commerce-dpd-base-rate">',
    '#suffix' => '</div">',
  );

  // Build a currency options list from all enabled currencies.
  $options = commerce_currency_get_code(TRUE);

  // If the current currency value is not available, add it now with a
  // message in the help text explaining it.
  if (empty($options[$shipping_service['base_rate']['currency_code']])) {
    $options[$shipping_service['base_rate']['currency_code']] = check_plain($shipping_service['base_rate']['currency_code']);

    $description = t('The currency set for this rate is not currently enabled. If you change it now, you will not be able to set it back.');
  }
  else {
    $description = '';
  }

  // If only one currency option is available, don't use a select list.
  if (count($options) == 1) {
    $currency_code = key($options);

    $form['dpd_shop_delivery']['amount']['#field_suffix'] = check_plain($currency_code);
    $form['dpd_shop_delivery']['amount']['#suffix'] = '</div>';

    $form['dpd_shop_delivery']['currency_code'] = array(
      '#type' => 'value',
      '#default_value' => $currency_code,
    );
  }
  else {
    $form['dpd_shop_delivery']['currency_code'] = array(
      '#type' => 'select',
      '#description' => $description,
      '#options' => $options,
      '#default_value' => $shipping_service['base_rate']['currency_code'],
      '#suffix' => '</div>',
    );
  }

  // Add support for base rates including tax.
  if (module_exists('commerce_tax')) {
    // Build an array of tax types that are display inclusive
    // That can be removed uder
    $inclusive_types = array();

    foreach (commerce_tax_types() as $name => $tax_type) {
      if ($tax_type['display_inclusive']) {
        $inclusive_types[$name] = $tax_type['title'];
      }
    }

    // Build an options array of tax rates of these types.
    $options = array();

    foreach (commerce_tax_rates() as $name => $tax_rate) {
      if (in_array($tax_rate['type'], array_keys($inclusive_types))) {
        $options[$inclusive_types[$tax_rate['type']]][$name] = t('Including @title', array('@title' => $tax_rate['title']));
      }
    }

    if (!empty($options)) {
      // Find the default value for the tax included element.
      $default = '';

      if (!empty($shipping_service['data']['include_tax'])) {
        $default = $shipping_service['data']['include_tax'];
      }

      $form['dpd_shop_delivery']['currency_code']['#title'] = '&nbsp;';

      $form['dpd_shop_delivery']['include_tax'] = array(
        '#type' => 'select',
        '#title' => t('Include tax in this rate'),
        '#description' => t('Saving a rate tax inclusive will bypass later calculations for the specified tax.'),
        '#options' => count($options) == 1 ? reset($options) : $options,
        '#default_value' => $default,
        '#required' => FALSE,
        '#empty_value' => '',
      );
    }
  }

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 40,
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save service'),
  );

  if (!empty($form_state['shipping_service']['name'])) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#suffix' => l(t('Cancel'), 'admin/commerce/config/shipping/services/dpd-shop-delivery'),
      '#submit' => array('commerce_dpd_shop_delivery_service_form_delete_submit'),
      '#weight' => 45,
    );
  }
  else {
    $form['actions']['submit']['#suffix'] = l(t('Cancel'), 'admin/commerce/config/shipping/services/dpd-shop-delivery');
  }

  return $form;
}

/**
 * Validate handler: ensures a valid base rate was entered for the service.
 */
function commerce_dpd_shop_delivery_service_form_validate($form, &$form_state) {
  // Ensure the rate amount is numeric.
  if (!is_numeric($form_state['values']['dpd_shop_delivery']['amount'])) {
    form_set_error('dpd_shop_delivery][amount', t('You must enter a numeric value for the base rate amount.'));
  }
  else {
    // Convert the decimal amount value entered to an integer based amount value.
    form_set_value($form['dpd_shop_delivery']['amount'], commerce_currency_decimal_to_amount($form_state['values']['dpd_shop_delivery']['amount'], $form_state['values']['dpd_shop_delivery']['currency_code']), $form_state);
  }
}

/**
 * Submit handler: saves the new or updated service.
 */
function commerce_dpd_shop_delivery_service_form_submit($form, &$form_state) {
  $shipping_service = $form_state['shipping_service'];

  // Update the shipping service array with values from the form.
  foreach (array(
             'name',
             'title',
             'display_title',
             'description',
             'amount',
             'currency_code'
           ) as $key) {
    $shipping_service[$key] = $form_state['values']['dpd_shop_delivery'][$key];
  }

  // If a tax was specified for inclusion, add it to the data array.
  if (!empty($form_state['values']['dpd_shop_delivery']['include_tax'])) {
    $shipping_service['data']['include_tax'] = $form_state['values']['dpd_shop_delivery']['include_tax'];
  }
  elseif (!empty($shipping_service['data']['include_tax'])) {
    unset($shipping_service['data']['include_tax']);
  }

  // Save the shipping service.
  unset($shipping_service['base_rate']);
  $op = commerce_dpd_shop_delivery_service_save($shipping_service);

  if (!$op) {
    drupal_set_message(t('The DPD Shop Delivery rate service failed to save properly. Please review the form and try again.'), 'error');
    $form_state['rebuild'] = TRUE;
  }
  else {
    drupal_set_message(t('DPD Shop Delivery rate service saved.'));
    $form_state['redirect'] = 'admin/commerce/config/shipping/services/dpd-shop-delivery';
  }
}

/**
 * Submit handler: redirects to the service delete confirmation form.
 *
 * @see commerce_dpd_shop_finder_service_form()
 */
function commerce_dpd_shop_delivery_service_form_delete_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/commerce/config/shipping/services/dpd-shop-delivery-' . strtr($form_state['shipping_service']['name'], '_', '-') . '/delete';
}

/**
 * Displays the edit form for an existing service.
 *
 * @param $name
 *   The machine-name of the service to edit.
 */
function commerce_dpd_shop_delivery_service_edit_page($name) {
  return drupal_get_form('commerce_dpd_shop_delivery_service_form', commerce_shipping_service_load($name));
}

/**
 * Builds the form for deleting services.
 */
function commerce_dpd_shop_delivery_service_delete_form($form, &$form_state, $shipping_service) {
  $form_state['shipping_service'] = $shipping_service;

  $form = confirm_form($form,
    t('Are you sure you want to delete the <em>%title</em> dpd rate service?', array('%title' => $shipping_service['title'])),
    'admin/commerce/config/shipping/services/dpd-shop-delivery',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for commerce_dpd_shop_finder_service_delete_form().
 */
function commerce_dpd_shop_delivery_service_delete_form_submit($form, &$form_state) {
  $shipping_service = $form_state['shipping_service'];

  commerce_dpd_shop_delivery_service_delete($shipping_service['name']);

  drupal_set_message(t('The DPD Shop Delivery rate service <em>%title</em> has been deleted.', array('%title' => $shipping_service['title'])));
  watchdog('commerce_dpd_shop_delivery', 'Deleted DPD Shop Delivery rate service <em>%title</em>.', array('%title' => $shipping_service['title']), WATCHDOG_NOTICE);

  $form_state['redirect'] = 'admin/commerce/config/shipping/services/dpd-shop-delivery';
}

