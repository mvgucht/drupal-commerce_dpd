<?php

/**
 * @file
 * Contains the theme callbacks for the DPD Shop Delivery module.
 */

/**
 * Implements template_preprocess_hook()
 * - theme_commerce_dpd_shop_delivery_shop_details
 */
function template_preprocess_commerce_dpd_shop_delivery_shop_details(&$vars) {
  // store raw values
  // add css files
  drupal_add_css(drupal_get_path('module', 'commerce_dpd_shop_delivery') . '/theme/commerce_dpd_shop_delivery.css');

  //Custom Variable for Shop Title
  if (!empty($vars['shop_details']->ShopAddress->Company)) {
    $vars['shop_title'] = $vars['shop_details']->ShopAddress->Company;
  }
  else {
    $vars['shop_title'] = 'test';
  }
  //Custom Variable for Shop Salutation
  if (!empty($vars['shop_details']->ShopAddress->Salutation)) {
    $vars['shop_salutation'] = $vars['shop_details']->ShopAddress->Salutation;
  }
  else {
    $vars['shop_salutation'] = '';
  }

  //Custom Variable for Shop Name
  if (!empty($vars['shop_details']->ShopAddress->Name)) {
    $vars['shop_name'] = $vars['shop_details']->ShopAddress->Name;
  }
  else {
    $vars['shop_name'] = '';
  }

  //Custom Variable for Shop Street
  if (!empty($vars['shop_details']->ShopAddress->Street)) {
    $vars['shop_street'] = $vars['shop_details']->ShopAddress->Street;
  }
  else {
    $vars['shop_street'] = '';
  }

  //Custom Variable for Shop HouseNo
  if (!empty($vars['shop_details']->ShopAddress->HouseNo)) {
    $vars['shop_house_no'] = $vars['shop_details']->ShopAddress->HouseNo;
  }
  else {
    $vars['shop_house_no'] = '';
  }

  //Custom Variable for Shop Country
  if (!empty($vars['shop_details']->ShopAddress->Country)) {
    $vars['shop_country'] = $vars['shop_details']->ShopAddress->Country;
  }
  else {
    $vars['shop_country'] = '';
  }

  //Custom Variable for Shop ZipCode
  if (!empty($vars['shop_details']->ShopAddress->ZipCode)) {
    $vars['shop_zip'] = $vars['shop_details']->ShopAddress->ZipCode;
  }
  else {
    $vars['shop_zip'] = '';
  }

  //Custom Variable for Shop City
  if (!empty($vars['shop_details']->ShopAddress->City)) {
    $vars['shop_city'] = $vars['shop_details']->ShopAddress->City;
  }
  else {
    $vars['shop_city'] = '';
  }

  //Custom Variable for Shop State
  if (!empty($vars['shop_details']->ShopAddress->State)) {
    $vars['shop_state'] = $vars['shop_details']->ShopAddress->State;
  }
  else {
    $vars['shop_state'] = '';
  }

  //Custom Variable for Shop Phone
  if (!empty($vars['shop_details']->ShopAddress->Phone)) {
    $vars['shop_phone'] = t('Phone') . ': ' . $vars['shop_details']->ShopAddress->Phone;
  }
  else {
    $vars['shop_phone'] = '';
  }

  //Custom Variable for Shop Phone
  if (!empty($vars['shop_details']->ShopAddress->Mail)) {
    $vars['shop_mail'] = t('Email') . ': ' . $vars['shop_details']->ShopAddress->Mail;
  }
  else {
    $vars['shop_mail'] = '';
  }

  //Custom Variable for Shop Website
  if (!empty($vars['shop_details']->Homepage)) {
    $vars['shop_homepage'] = l($vars['shop_details']->Homepage, 'http://' . $vars['shop_details']->Homepage, array('absolute' => TRUE));
  }
  else {
    $vars['shop_homepage'] = '';
  }

  //Custom Variable for Shop Distance
  if (!empty($vars['shop_details']->GeoData->Distance)) {
    $vars['shop_distance'] = round($vars['shop_details']->GeoData->Distance, 2) . t('km');
  }
  else {
    $vars['shop_distance'] = '';
  }

  if (isset($vars['shop_details']->OpeningHoursList)) {
    $opening_times = $vars['shop_details']->OpeningHoursList;
    $header = array();

    foreach ($opening_times as $time) {
      $wd = $time->WeekDay;
      $tlist = $time->OpenTimeList;
      foreach ($tlist as $key => $t) {
        $rows[$wd][$wd] = $wd;
        $rows[$wd]['time_from_' . $key] = $t->TimeFrom;
        $rows[$wd]['time_end_' . $key] = $t->TimeEnd;
      }
    }
  }

  if (!empty($rows)) {

    //dpm($rows);
    $attributes = array(
      'class' => array('commerce-dpd-shop-delivery-shop-timetable'),
    );

    $vars['shop_opening_times'] = theme('table',
      array(
        'header' => $header,
        'rows' => $rows,
        'attributes' => $attributes,
      )
    );

  }
  else {
    $vars['shop_opening_times'] = '';
  }
}
