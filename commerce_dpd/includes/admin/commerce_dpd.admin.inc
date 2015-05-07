<?php

/**
 * @file Contains the page and form callbacks for the dpd module.
 */

/**
 * The settings form for the configuration panel.
 */
function commerce_dpd_settings_form($form, &$form_state) {
  $form['groups'] = array(
    '#type' => 'vertical_tabs'
  );

  $default_values = commerce_dpd_settings(array());

  if (commerce_dpd_check_api() === FALSE) {
    drupal_set_message(t('DPD API not reachable!'), 'warning', FALSE);
  }

  // Check if there is already the required tcpdf and fdpi library installed
  if (!commerce_dpd_get_library('tcpdf')) {
    drupal_set_message(t('You need to install TCPDF Library in order to use the Bulk Print Action to print multiple DPD Labels!'));
  }
  if (!commerce_dpd_get_library('fpdi')) {
    drupal_set_message(t('You need to install FPDI Library in order to use the Bulk Print Action to print multiple DPD Labels!'));
  }

  $form['commerce_dpd_api'] = array(
    '#type' => 'fieldset',
    '#title' => t('DPD API Settings'),
    '#collapsible' => TRUE,
    '#group' => 'groups',
    '#weight' => 1,
  );

  $form['commerce_dpd_mapping'] = array(
    '#type' => 'fieldset',
    '#title' => t('DPD Mapping'),
    '#collapsible' => TRUE,
    '#group' => 'groups',
    '#weight' => 2,
  );

  $form['commerce_dpd_label'] = array(
    '#type' => 'fieldset',
    '#title' => t('DPD Label Print'),
    '#collapsible' => TRUE,
    '#group' => 'groups',
    '#weight' => 3,
  );
	
	$form['commerce_dpd_time_logging'] = array(
    '#type' => 'fieldset',
    '#title' => t('DPD Time Logging'),
    '#collapsible' => TRUE,
    '#group' => 'groups',
    '#weight' => 4,
  );

  $form['commerce_dpd_api']['stage_live_option'] = array(
    '#type' => 'select',
    '#options' => array(
      'sandbox' => t('Stage'),
      'live' => t('Live'),
    ),
    '#title' => t('Choose Server'),
    '#description' => t('Contact DPD to obtain your API credentials.'),
    '#required' => TRUE,
    '#default_value' => isset($default_values['stage_live_option']) ? $default_values['stage_live_option'] : '',
  );

  $form['commerce_dpd_api']['delisID'] = array(
    '#type' => 'textfield',
    '#title' => t('DelisID'),
    '#description' => t('Contact DPD to obtain your API credentials.'),
    '#required' => TRUE,
    '#default_value' => isset($default_values['delisID']) ? $default_values['delisID'] : '',
  );

  $form['commerce_dpd_api']['password'] = array(
    '#type' => 'password',
    '#title' => t('Password'),
    '#description' => t('Contact DPD to obtain your API credentials.'),
    '#required' => TRUE,
    '#default_value' => isset($default_values['password']) ? $default_values['password'] : '',
  );
	
	$form['commerce_dpd_api']['Name1'] = array(
    '#type' => 'textfield',
    '#title' => t('Name1'),
    '#description' => t('Contact DPD to obtain your API credentials.'),
    '#required' => TRUE,
    '#default_value' => isset($default_values['Name1']) ? $default_values['Name1'] : '',
  );
	$form['commerce_dpd_api']['Street'] = array(
    '#type' => 'textfield',
    '#title' => t('Street'),
    '#description' => t('Contact DPD to obtain your API credentials.'),
    '#required' => TRUE,
    '#default_value' => isset($default_values['Street']) ? $default_values['Street'] : '',
  );
	$form['commerce_dpd_api']['HouseNo'] = array(
    '#type' => 'textfield',
    '#title' => t('HouseNo'),
    '#description' => t('Contact DPD to obtain your API credentials.'),
    '#required' => TRUE,
    '#default_value' => isset($default_values['HouseNo']) ? $default_values['HouseNo'] : '',
  );
	$form['commerce_dpd_api']['ZipCode'] = array(
    '#type' => 'textfield',
    '#title' => t('ZipCode'),
    '#description' => t('Contact DPD to obtain your API credentials.'),
    '#required' => TRUE,
    '#default_value' => isset($default_values['ZipCode']) ? $default_values['ZipCode'] : '',
  );
	$form['commerce_dpd_api']['City'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#description' => t('Contact DPD to obtain your API credentials.'),
    '#required' => TRUE,
    '#default_value' => isset($default_values['City']) ? $default_values['City'] : '',
  );
	$form['commerce_dpd_api']['Country'] = array(
    '#type' => 'textfield',
    '#title' => t('Country'),
    '#description' => t('Contact DPD to obtain your API credentials.'),
    '#required' => TRUE,
    '#default_value' => isset($default_values['Country']) ? $default_values['Country'] : '',
  );

  $form['commerce_dpd_mapping']['salutation'] = array(
    '#type' => 'textfield',
    '#title' => t('Salutation'),
    '#description' => t('You may use tokens for this field.'),
    '#default_value' => isset($default_values['salutation']) ? $default_values['salutation'] : '',
  );
  /*
  $form['commerce_dpd_mapping']['phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone'),
    '#description' => t('You may use tokens for this field.'),
    '#default_value' => isset($default_values['phone']) ? $default_values['phone'] : '',
  );
  */
  $form['commerce_dpd_mapping']['weight'] = array(
    '#type' => 'textfield',
    '#title' => t('Weight'),
    '#description' => t('You may use tokens for this field.'),
    '#default_value' => isset($default_values['weight']) ? $default_values['weight'] : '',
  );

  $form['commerce_dpd_mapping']['content'] = array(
    '#type' => 'textfield',
    '#title' => t('Content'),
    '#description' => t('You may use tokens for this field.'),
    '#default_value' => isset($default_values['content']) ? $default_values['content'] : '',
  );

  $form['commerce_dpd_mapping']['reference1'] = array(
    '#type' => 'textfield',
    '#title' => t('Reference1'),
    '#description' => t('You may use tokens for this field.'),
    '#default_value' => isset($default_values['reference1']) ? $default_values['reference1'] : '',
  );

  $form['commerce_dpd_mapping']['reference2'] = array(
    '#type' => 'textfield',
    '#title' => t('Reference2'),
    '#description' => t('You may use tokens for this field.'),
    '#default_value' => isset($default_values['reference2']) ? $default_values['reference2'] : '',
  );

  if (module_exists('token')) {
    $form['commerce_dpd_mapping']['token'] = array(
      '#type' => 'fieldset',
      '#title' => t('Click for Info of available Tokens'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['commerce_dpd_mapping']['token']['token_help'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('commerce-product', 'commerce-order'),
    );
  }

  $form['commerce_dpd_label']['label_size'] = array(
    '#type' => 'select',
    '#options' => _commerce_dpd_label_size_options(),
    '#title' => t('Select Label Format'),
    '#description' => t('Choose your preferred Label format.'),
    '#required' => TRUE,
    '#default_value' => isset($default_values['label_size']) ? $default_values['label_size'] : '',
  );
	
	$form['commerce_dpd_time_logging']['time_logging_option'] = array(
    '#type' => 'select',
    '#options' => array(
      'on' => t('On'),
      'off' => t('Off'),
    ),
    '#title' => t('Web service time logging'),
    '#description' => t('This will monitor and time every dpd web service call and log it remotely. The logging call is timed out after max 1 second, but if you prefer you can always disable it here.'),
    '#required' => TRUE,
    '#default_value' => isset($default_values['time_logging_option']) ? $default_values['time_logging_option'] : '',
  );

  $form['debug'] = array(
    '#type' => 'fieldset',
    '#title' => t('Debugging'),
    '#collapsible' => TRUE,
    '#collapsed' => !($default_values['debug_messages'] || $default_values['debug_log']),
  );
  $form['debug']['debug_log'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log debug information to the system log'),
    '#default_value' => $default_values['debug_log'],
  );
  $form['debug']['debug_messages'] = array(
    '#type' => 'radios',
    '#title' => t('Show debug information'),
    '#default_value' => $default_values['debug_messages'],
    '#options' => array(
      0 => t('Never'),
      2 => t('In case of errors'),
      1 => t('Always'),
    ),
    '#description' => t('Debug information is only shown for Commerce DPD requests and is visible for users having the permission <a href="!url">%link</a>.', array(
        '%link' => t('Access the DPD API debugging messages'),
        '!url' => url('admin/people/permissions', array('fragment' => 'module-commerce_dpd'))
      )),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Validate callback for commerce_dpd_settings_form()
 */
function commerce_dpd_settings_form_validate($form, &$form_state) {
  $values = &$form_state['values'];
}

/**
 * Submit callback for commerce_dpd_settings_form()
 */
function commerce_dpd_settings_form_submit($form, &$form_state) {

  form_state_values_clean($form_state);
  $values = &$form_state['values'];

  // Get all current stored settings:
  $current_settings = commerce_dpd_settings(array());

  // Remove any values not in settings info:
  $settings = array_intersect_key($values, $current_settings);

  // Merge stored settings:
  $settings += $current_settings;

  // Save new merged settings:
  variable_set('commerce_dpd_settings', $settings);

  drupal_set_message(t('The configuration options have been saved.'));

}
