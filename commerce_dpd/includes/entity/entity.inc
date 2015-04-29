<?php

/**
 * @file Label custom entity class.
 */

class CommerceDpdLabel extends Entity {

  /**
   * Override defaultUri().
   */
  protected function defaultUri() {
    return array('path' => 'admin/commerce/orders/dpd-labels/label/' . $this->identifier());
  }

  /**
   * Provide defaultLabel().
   */
  protected function defaultLabel() {
    return $this->title;
  }

}
