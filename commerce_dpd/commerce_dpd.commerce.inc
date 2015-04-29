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
  );
}
