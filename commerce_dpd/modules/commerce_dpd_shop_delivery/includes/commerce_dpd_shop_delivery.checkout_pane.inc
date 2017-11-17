<?php

/**
 * @file
 *   Checkout pane hooks
 */

/**
 * commerce_dpd_order_shop_pane: form callback.
 */
function commerce_dpd_shop_delivery_order_shop_pane_checkout_form($form, &$form_state, $checkout_pane, $order) {
  $pane_form = array();
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  $dpd_shop = $order_wrapper->dpd_shop->value();
  if ($dpd_shop) {
    $dpd_shop_lon = $dpd_shop->shop_lon;
    $dpd_shop_lat = $dpd_shop->shop_lat;

    $dpd_selected_shop_details = commerce_dpd_rest_api_get_shops_by_geodata(
      $dpd_shop_lon,
      $dpd_shop_lat,
      1);
  }


  if (!empty($dpd_shop_lon) && !empty($dpd_shop_lat)) {
    $pane_form['commerce_dpd_shop_details'] = array(
      '#markup' => theme('commerce_dpd_shop_delivery_shop_details', array(
          'shop_details' => $dpd_selected_shop_details[0],
        )
      ),
    );
  }


  return $pane_form;
}
