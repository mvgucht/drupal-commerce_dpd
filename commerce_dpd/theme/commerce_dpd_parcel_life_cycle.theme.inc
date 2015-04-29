<?php

function template_preprocess_commerce_dpd_parcel_life_cycle_results(&$vars) {
  // add css files
  drupal_add_css(drupal_get_path('module', 'commerce_dpd_parcel_life_cycle') . '/theme/commerce_dpd_parcel_life_cycle.css');


  $vars['shipment_parcel_number_label'] = t('DPD Parcel Number');
  $vars['shipment_parcel_number'] = $vars['parcel_number'];
  $vars['shipment_service_label'] = $vars['service_label'];
  $vars['shipment_service_value'] = $vars['service_value'];

  $vars['shipment_states_label'] = t('DPD Shipment States');

  $header = array();
  $rows = $vars['states'];

  $vars['shipment_states'] = theme('table', array(
    'header' => $header,
    'rows' => $rows
  ));

}
