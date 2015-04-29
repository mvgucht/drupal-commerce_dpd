<?php

/**
 * @file
 * Views integration for Commerce DPD.
 */

/**
 * Implements hook_views_data()
 * Additional Data for Commerce DPD Views.
 */
function commerce_dpd_views_data() {
  $data = array();

  // Tracking object data:
  $data['commerce_dpd_orders']['table']['group'] = t('Commerce DPD Orders');
  $data['commerce_dpd_orders']['table']['base'] = array(
    'field' => 'id',
    'title' => t('Commerce DPD Orders'),
    'help' => t('Stores Commerce DPD Shipping methods and services associated with an order.'),
  );

  // For other base tables, explain how we join.
  // 'left_field' is the primary key in the referenced table.
  // 'field' is the foreign key in this table.
  $data['commerce_dpd_orders']['table']['join'] = array(
    'commerce_order' => array(
      'left_field' => 'order_id',
      'field' => 'order_id',
    ),
  );

  // Expose the order ID.
  $data['commerce_dpd_orders']['order_id'] = array(
    'title' => t('Order ID'),
    'help' => t('The unique internal identifier of the order.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'commerce_order_handler_argument_order_order_id',
      'name field' => 'order_label',
      'numeric' => TRUE,
      'validate type' => 'order_id',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'commerce_order',
      'field' => 'order_id',
      'label' => t('Order', array(), array('context' => 'a drupal commerce order')),
    ),
  );

  // Expose the shipping method:
  $data['commerce_dpd_orders']['shipping_method'] = array(
    'title' => t('DPD Shipping Method'),
    'help' => t('The DPD Shipping Method selected on the order.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the shipping service:
  $data['commerce_dpd_orders']['shipping_service'] = array(
    'title' => t('DPD Shipping Service'),
    'help' => t('The DPD Shipping Service selected on the order.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;

}
