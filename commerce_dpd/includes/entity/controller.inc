<?php

/**
 * @file Custom controller for the label entity.
 */

class CommerceDpdLabelController extends EntityAPIController {

  /**
   * Override the save method.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    if (isset($entity->is_new)) {
      $entity->created = REQUEST_TIME;
    }

    $entity->changed = REQUEST_TIME;
    return parent::save($entity, $transaction);
  }

  /**
   * Build Entity Content Function
   */
  public function buildContent($entity, $view_mode = 'default', $langcode = NULL, $content = array()) {

    /*
    // Make Description themed like default fields.
    $content['title'] = array(
      '#theme' => 'field',
      '#weight' => 0,
      '#title' =>t('Title'),
      '#access' => TRUE,
      '#label_display' => 'inline',
      '#view_mode' => 'default',
      '#language' => LANGUAGE_NONE,
      '#field_name' => 'field_fake_title',
      '#field_type' => 'text',
      '#entity_type' => 'commerce_dpd_label',
      '#bundle' => $entity->type,
      '#items' => array(array('value' => $entity->title)),
      '#formatter' => 'text_default',
      0 => array('#markup' => check_plain($entity->title))
    );

    // Make Description themed like default fields.
    $content['description'] = array(
      '#theme' => 'field',
      '#weight' => 0,
      '#title' =>t('Description'),
      '#access' => TRUE,
      '#label_display' => 'inline',
      '#view_mode' => 'default',
      '#language' => LANGUAGE_NONE,
      '#field_name' => 'field_fake_description',
      '#field_type' => 'text',
      '#entity_type' => 'commerce_dpd_label',
      '#bundle' => $entity->type,
      '#items' => array(array('value' => $entity->description)),
      '#formatter' => 'text_default',
      0 => array('#markup' => check_plain($entity->description))
    );

    // Make Description themed like default fields.
    $content['created'] = array(
      '#theme' => 'field',
      '#weight' => 0,
      '#title' =>t('Created'),
      '#access' => TRUE,
      '#label_display' => 'inline',
      '#view_mode' => 'default',
      '#language' => LANGUAGE_NONE,
      '#field_name' => 'field_fake_created',
      '#field_type' => 'text',
      '#entity_type' => 'commerce_dpd_label',
      '#bundle' => $entity->type,
      '#items' => array(array('value' => $entity->created)),
      '#formatter' => 'text_default',
      0 => array('#markup' => check_plain($entity->created))
    );

    // Make Description themed like default fields.
    $content['changed'] = array(
      '#theme' => 'field',
      '#weight' => 0,
      '#title' =>t('Changed'),
      '#access' => TRUE,
      '#label_display' => 'inline',
      '#view_mode' => 'default',
      '#language' => LANGUAGE_NONE,
      '#field_name' => 'field_fake_changed',
      '#field_type' => 'text',
      '#entity_type' => 'commerce_dpd_label',
      '#bundle' => $entity->type,
      '#items' => array(array('value' => $entity->changed)),
      '#formatter' => 'text_default',
      0 => array('#markup' => check_plain($entity->changed))
    );
    */
    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }
}
