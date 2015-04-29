<?php

/**
 * @file UI and forms for the Commerce DPD Label Functionality
 */

/**
 * The Request Label Form.
 */
function commerce_dpd_label_admin_form($form, &$form_state, $order) {

  $default_values = commerce_dpd_settings();

  $form['#attached']['css'][] = drupal_get_path('module', 'commerce_dpd') . '/theme/css/form.css';

  $form['ship_date'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ship date'),
    //'#description' =>  t('Please enter your required ship date.'),
    '#attributes' => array('class' => array('commerce-dpd-label-ship-date clearfix')),
  );

  $form['ship_date']['dd'] = array(
    '#title' => 'DD',
    '#type' => 'textfield',
    '#attributes' => array('placeholder' => t('DD')),
    '#size' => '2',
    '#maxlength' => 2,
    '#required' => TRUE,
    '#default_value' => _commerce_dpd_label_get_default_day(),
  );

  $form['ship_date']['mm'] = array(
    '#title' => 'MM',
    '#type' => 'textfield',
    '#attributes' => array('placeholder' => t('MM')),
    '#size' => '2',
    '#maxlength' => 2,
    '#required' => TRUE,
    '#default_value' => _commerce_dpd_label_get_default_month(),
  );

  $form['ship_date']['yyyy'] = array(
    '#title' => 'YYYY',
    '#type' => 'textfield',
    '#attributes' => array('placeholder' => t('YYYY')),
    '#size' => '4',
    '#maxlength' => 4,
    '#required' => TRUE,
    '#default_value' => _commerce_dpd_label_get_default_year(),
  );

  $no_pickup_days = commerce_dpd_rest_api_zip_code_rules_no_pickup_days();
  foreach ($no_pickup_days as $no_pickup_day) {
    if (strtotime($no_pickup_day) > strtotime(date('d.m.Y'))) {
      $future_no_pickup_days[] = $no_pickup_day;
    }
  }
  if (!empty($future_no_pickup_days)) {
    $no_pickup_days_markup = t('There are no parcel pick-up days') . ':';
    $no_pickup_days_markup .= theme('item_list', array('items' => $future_no_pickup_days));
    $no_pickup_days_markup .= t('Please use other ship dates.');
    $form['ship_date']['no_pickup_days'] = array(
      '#type' => 'item',
      '#markup' => $no_pickup_days_markup,
    );
  }

  $form['label_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Label format settings'),
    '#collapsed' => TRUE,
    '#collapsible' => TRUE,
  );

  $form['label_settings']['label_size'] = array(
    '#type' => 'select',
    '#options' => _commerce_dpd_label_size_options(),
    '#title' => t('Select Label Format'),
    '#description' => t('Choose your preferred Label format.'),
    '#required' => TRUE,
    '#default_value' => isset($default_values['label_size']) ? $default_values['label_size'] : '',
  );

  $form['label_settings']['label_position'] = array(
    '#type' => 'select',
    '#options' => _commerce_dpd_label_start_position_options(),
    '#title' => t('Select Label Position'),
    '#description' => t('Choose your preferred Label position.'),
    '#required' => TRUE,
    '#default_value' => isset($default_values['label_position']) ? $default_values['label_position'] : '',
    '#states' => array(
      'visible' => array(   // action to take.
        ':input[name=label_size]' => array('value' => 'PDF_A4'),
      ),
    ),
  );

  $form['#order'] = $order;

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Print Label'),
  );

  return $form;

}

/**
 * Form callback: validate.
 */
function commerce_dpd_label_admin_form_validate($form, &$form_state) {
  $values = &$form_state['values'];
  if (!empty($values['dd']) || !empty($values['mm']) || !empty($values['yyyy'])) {
    // Day value validation.
    if (strlen($values['dd']) < 2) {
      form_set_error('dd');
      form_set_error('ship_date', t('Date not valid!'));
    }
    // Month value validation.
    if (strlen($values['mm']) < 2) {
      form_set_error('mm');
      form_set_error('ship_date', t('Date not valid!'));
    }
    // Year value validation.
    if (strlen($values['yyyy']) < 4) {
      form_set_error('yyyy');
      form_set_error('ship_date', t('Date not valid!'));
    }
    if (checkdate($values['mm'], $values['dd'], $values['yyyy'])) {
      $ship_date = $values['dd'] . '.' . $values['mm'] . '.' . $values['yyyy'];
      // Future date validation.
      if (strtotime($ship_date) < strtotime(date('d.m.Y'))) {
        form_set_error('ship_date', t('Given date is smaller than today!'));
      }
      // DPD ZipCodeRules NoPickupDays validation.
      $no_pickup_days = commerce_dpd_rest_api_zip_code_rules_no_pickup_days();
      if (is_array($no_pickup_days) && in_array($ship_date, $no_pickup_days)) {
        form_set_error('ship_date', t('No parcel pick-up is possible on this date. Please try another ship date.'));
      }
    }
    else {
      form_set_error('mm');
      form_set_error('dd');
      form_set_error('yyyy');
      form_set_error('ship_date', t('Date not valid!'));
    }
  }
}

/**
 * Form callback: submit.
 */
function commerce_dpd_label_admin_form_submit($form, &$form_state) {
  if (isset($form_state['build_info']['args'][0])) {
    // Get the order object from the $form_state
    $order = $form_state['build_info']['args'][0];
    $values = $form_state['values'];
    $ship_date = $values['dd'] . '.' . $values['mm'] . '.' . $values['yyyy'];
    // Prepare the $settings array for the dpd order
    $settings = array(
      'ShipDate' => date('m.d.Y', strtotime($ship_date)),
      'LabelSize' => $values['label_size'],
      'LabelStartPosition' => $values['label_position'],
    );

    // Try to create DPD Label Entity
    $commerce_dpd_label_path = commerce_dpd_label_create_label($order, $settings, 'single');
    if ($commerce_dpd_label_path) {
      // Jump To created Entity
      $path = $commerce_dpd_label_path;
      $_GET['destination'] = $path;
      $form_state['redirect'] = $path;
    }
    else {
      // No label created: errors, existing label, ... .
    }
  }
}
