<?php

/**
 * Implements hook_commerce_dpd_settings_info().
 */
function commerce_dpd_commerce_dpd_settings_info() {
	
  return array(
		'stage_live_option' => array(
      'default' => 'stage',
    ),
    'delisID' => array(
      'default' => '',
    ),
    'password' => array(
      'default' => '',
    ),
		'Name1' => array(
      'default' => '',
    ),
		'Name2' => array(
      'default' => '',
    ),
		'Street' => array(
      'default' => '',
    ),
		'HouseNo' => array(
      'default' => '',
    ),
		'ZipCode' => array(
      'default' => '',
    ),
		'City' => array(
      'default' => '',
    ),
		'Country' => array(
      'default' => '',
    ),
    'debug_messages' => array(
      'default' => 0,
    ),
    'debug_log' => array(
      'default' => FALSE,
    ),
    'label_size' => array(
      'default' => 'PDF_A4',
    ),
		'salutation' => array(
      'default' => '',
    ),
    'weight' => array(
      'default' => '',
    ),
    'content' => array(
      'default' => '',
    ),
    'reference1' => array(
      'default' => '',
    ),
    'reference2' => array(
      'default' => '',
    ),
		'time_logging_option' => array(
      'default' => 'on',
    )
  );
}
