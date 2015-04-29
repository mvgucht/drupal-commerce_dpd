<?php

/**
 * @file
 * Provides metadata for the entity.
 */

/*
 * Implements hook_entity_property_info_alter().
 */
function commerce_dpd_shop_delivery_entity_property_info_alter(&$info) {
  // Commerce Line item
  if (isset($info['commerce_line_item'])) {
    // Line item bundles
    if (isset($info['commerce_line_item']['bundles'])) {
      // Shipping line items
      if (isset($info['commerce_line_item']['bundles']['shipping']['properties'])) {
        $info['commerce_line_item']['bundles']['shipping']['properties']['dpd_shop'] = array(
          'label' => t('DPD Shop'),
          'type' => 'struct',
          'description' => t('The DPD Shop selected for this shipping line item.'),
          'getter callback' => 'commerce_dpd_shop_delivery_line_item_property_get',
          'property info' => commerce_dpd_shop_delivery_line_item_shop_property_info_callback(),
          'computed' => TRUE,
        );
      }
    }
  }

  // Commerce Order
  if (isset($info['commerce_order']) && isset($info['commerce_order']['properties'])) {
    $order_properties = &$info['commerce_order']['properties'];
    $order_properties['dpd_shop'] = array(
      'label' => t('DPD Shop'),
      'type' => 'struct',
      'description' => t('The DPD Shop selected for this order.'),
      'getter callback' => 'commerce_dpd_shop_delivery_order_property_get',
      'property info' => commerce_dpd_shop_delivery_line_item_shop_property_info_callback(),
      'computed' => TRUE,
    );
    $order_properties['dpd_shop_id'] = array(
      'label' => t('DPD Shop ID'),
      'type' => 'integer',
      'description' => t('The DPD Shop ID selected for this order.'),
      'getter callback' => 'commerce_dpd_shop_delivery_order_property_get',
      'computed' => TRUE,
    );
  }
}
