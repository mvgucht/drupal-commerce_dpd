<?php

/**
 * @file A custom class to add functionality to the external PDF Libraries.
 */

require_once commerce_dpd_get_library('tcpdf') . '/tcpdf.php';
require_once commerce_dpd_get_library('fpdi') . '/fpdi.php';

/**
 * Class extending FPDI Class.
 */
class CommerceDpd_concat_pdf extends FPDI {
  var $files = array();

  /**
   * Set the files.
   */
  function setFiles($files) {
    $this->files = $files;
  }

  /**
   * Merge the PDF files together.
   */
  function concat() {
    foreach ($this->files AS $file) {
      $pagecount = $this->setSourceFile($file);
      for ($i = 1; $i <= $pagecount; $i++) {
        $tplidx = $this->ImportPage($i);
        $s = $this->getTemplatesize($tplidx);
        $this->setPrintHeader(FALSE);
        $this->setPrintFooter(FALSE);
        $this->AddPage('P', array($s['w'], $s['h']));
        $this->useTemplate($tplidx);
      }
    }
  }
}
