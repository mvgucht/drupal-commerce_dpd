<?php

/**
 * @file Admin track and trace form.
 */

/**
 * Admin track and trace form.
 */
function commerce_dpd_parcel_life_cycle_admin_form($form, &$form_state, $order) {
  $wrapper = entity_metadata_wrapper('commerce_order', $order);
  $parcel_life_cycle_object = $wrapper->dpd_parcel_life_cycle_object->value();
  // Waiting for a working setOrder Request fo full fill:
  if (isset($form_state['values']) && isset($form_state['values']['parcel_number'])) {
    $markup = commerce_dpd_parcel_life_cycle_get_markup($form_state['values']['parcel_number']);
  }
  else {
    $markup = '';
  }

  $form['parcel_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Parcel number'),
    '#default_value' => !empty($parcel_life_cycle_object) ? $parcel_life_cycle_object->parcel_number : '',
    '#required' => TRUE,
  );

  $form['update'] = array(
    '#type' => 'button',
    '#value' => t('Update'),
    '#description' => t('This will save the tracking number for this order and look for updates to the status'),
  );

  $form['parcel_life_cycle']['#markup'] = $markup;
  $form['#order'] = $order;
  return $form;

}

/**
 * Get markup from Parcel Number.
 *
 * @param string $parcel_number
 *    The parcel number to track.
 * @return array $output
 *    The rendered markup.
 */
function commerce_dpd_parcel_life_cycle_get_markup($parcel_number) {
  $parcel_object = commerce_dpd_rest_api_parcel_tracking_data($parcel_number);
  if ($parcel_object) {
    $service_label = commerce_dpd_parcel_life_cycle_shipment_service_label($parcel_object);
    $service_value = commerce_dpd_parcel_life_cycle_shipment_service_value($parcel_object);
    $states = commerce_dpd_parcel_life_cycle_shipment_states($parcel_object);
    $output = theme('commerce_dpd_parcel_life_cycle_results', array(
      'parcel_number' => $parcel_number,
      'service_label' => $service_label,
      'service_value' => $service_value,
      'states' => $states,
    ));
  }
  else {
    $output = t('No Data available!');
  }

  return render($output);
}

/**
 * Form callback: submit track-and-trace admin form.
 */
function commerce_dpd_parcel_life_cycle_admin_form_submit(&$form, &$form_state) {
  // Update or insert a tracking object record:
  if (empty($form['#dpd_parcel_life_cycle_object'])) {
    $parcel_object = commerce_dpd_rest_api_parcel_tracking_data($form_state['values']['parcel_number']);
  }
  else {
    $parcel_object = $form['#dpd_parcel_life_cycle_object'];
    $parcel_object->parcel_number = $form_state['values']['tracking_number'];
  }
}
