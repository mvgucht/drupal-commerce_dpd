<?php

/*
 * Implements hook_entity_property_info_alter().
 */
function commerce_dpd_entity_property_info_alter(&$info) {
  // Put the DPD shipment info on the order
  if (isset($info['commerce_order'])) {
    $info['commerce_order']['properties']['dpd_shipment_object'] = array(
      'type' => 'struct',
      'label' => t('DPD shipping method'),
      'getter callback' => 'commerce_dpd_order_property_getter',
      'property info' => array(
        'shipping_method' => array(
          'type' => 'text',
          'label' => t('DPD Shipping Method'),
          'getter callback' => 'commerce_dpd_order_property_getter',
        ),
      )
    );
    $info['commerce_order']['properties']['dpd_parcel_life_cycle_object'] = array(
      'type' => 'struct',
      'label' => t('DPD Parcel number'),
      'getter callback' => 'commerce_dpd_parcel_life_cycle_order_property_getter',
      'property info' => array(
        'parcel_number' => array(
          'type' => 'text',
          'label' => t('Parcel number'),
          'getter callback' => 'commerce_dpd_parcel_life_cycle_order_property_getter',
        ),
      )
    );
  }
  if (isset($info['commerce_dpd_label'])) {
    $properties = &$info['commerce_dpd_label']['properties'];
    $properties['title'] = array(
      'label' => t("Title"),
      'type' => 'text',
      'schema field' => 'title',
      'description' => t("The title of the entity."),
      'setter callback' => 'entity_property_verbatim_set',
      'getter callback' => 'entity_property_verbatim_get',
    );
    $properties['description'] = array(
      'label' => t("Description"),
      'type' => 'text',
      'schema field' => 'description',
      'description' => t("The Description of the entity."),
      'setter callback' => 'entity_property_verbatim_set',
      'getter callback' => 'entity_property_verbatim_get',
    );
    $properties['created'] = array(
      'label' => t("Date created"),
      'type' => 'date',
      'description' => t("The date the node was posted."),
      'schema field' => 'created',
    );
    $properties['changed'] = array(
      'label' => t("Date changed"),
      'type' => 'date',
      'schema field' => 'changed',
      'description' => t("The date the node was most recently updated."),
    );
  }
}
