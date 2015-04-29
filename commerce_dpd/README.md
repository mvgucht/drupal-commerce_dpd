CONTENTS OF THIS FILE
----------------------

  * Introduction
  * Requirements
  * Installation
  * Configuration
  * Features


INTRODUCTION
------------

This Module will integrate two very common DPD shipping products
"classic_predict" and "shop_delivery" as two separate shipping methods.
The Module consists of three modules.

 x commerce_dpd (DPD Core module)
 x commerce_dpd_classic_predict (DPD Shipping method module)
 x commerce_dpd_shop_delivery (DPD Shipping method module)

DPD Cloud API Methods have been integrated into a custom PHP Library Class
to ensure highly accessibility for other Developers.

REQUIREMENTS

To use this Module you will need to have the following Drupal Modules installed:

x commerce
x commerce_shipping
x commerce_order
x leaflet
x leaflet_more_maps
x pdf

To use this Module you will also need the following PHP Library installed:
https://github.com/DPDBeNeLux/php-DPD_Cloud_Class

It should be included in your sites/all/libraries/dpd-cloud-rest

When you look inside the folder you should have the following structure:
sites/all/libraries/dpd-cloud-rest
 DPD.api.class.inc
 examples.php
 README.md

You also can use the attached MAKE file for that purpose. If you are not familiar
with MAKE files you can also install it manually.

In order to use the PDF field formatter properly you would also need the PDF.js
library installed to sites/all/libraries/pdf.js.

When you look inside the folder you should have the following structure:

sites/all/libraries/pdf.js
 build
 web
 LICENSE

To use the integrated Bulk Label Print functionality you have to install
two external PDF Libraries. The one is called TCPDF (http://www.tcpdf.org/)
and the other one called FPDI (http://www.setasign.com/products/fpdi/about/).

The Libraries will merge more PDF files to a single one.
And this is exactly what you will need for the Label Bulk Print option.

You can install the Libraries directly from the vendor websites,
or you can grab them on the following Github-Websites:

x https://github.com/tecnickcom/TCPDF
x https://github.com/mark9000/FPDI

Place the libraries inside sites/all/libraries, that finally you have a folder
structure like below:

sites/all/libraries/tcpdf
 tcpdf.php
 .
 .
sites/all/libraries/fpdi
 fpdi.php
 .
 .

INSTALLATION
------------
1. Copy commerce_dpd Module folder to modules directory.
   In most cases that would be sites/all/modules
2. At admin/modules/list enable the commerce_dpd module.
3. At admin/modules/list also enable the attached sub modules
   for the shipping methods.
   1. commerce_dpd_shop_delivery
   2. commerce_dpd_classic_predict
4. Enable permissions at admin/user/permissions.

CONFIGURATION
-------------

1. Configure the module at admin/commerce/config/dpd
2. Configure the shipping method commerce_dpd_shop_delivery
   at admin/commerce/config/shipping/methods/dpd-shop-delivery/edit
3. Configure the shipping method commerce_dpd_classic_predict
   at admin/commerce/config/shipping/methods/dpd-classic-predict/edit
4. Add the shipping services for each Shipping Method at
   admin/commerce/config/shipping

FEATURES
--------

x Interactive Leaflet Map for DPD Shop Selection
x Creating single DPD Label
x Creating DPD Labels for multiple Orders
x DPD Life Cycle Parcel Tracking
