<?php

/**
 * @file
 * Default implementation of the shopping cart block template.
 *
 * Available variables:
 * - $point_details: A Kiala Point details array
 * @ref http://locateandselect.kiala.com/info/ws
 *    - shortID
 *    - status
 *    - address
 *    - remark
 *    - openingHours
 *    - picture
 *    - coordinate
 *    - distance
 *    - label
 *
 * - $available: TRUE if point is available
 * - $status_message: The point's status message vale
 * - $picture_image: rendered image tag of the point's picture
 * - $show_more_link: TRUE to show view more link
 * - $more_link_text: more link text
 * - $more_link_url: full url to view more
 *
 * @see template_preprocess_commerce_kiala_point_details()
 */
?>

<?php if (!empty($shop_title)): ?>
  <h4 class="dpd-shop-detail"><?php print $shop_title; ?></h4>
<?php endif; ?>

<?php if (!empty($shop_distance)): ?>
  <span class="dpd-shop-detail-line"><?php print $shop_distance; ?></span>
<?php endif; ?>

<?php if (!empty($shop_street) || !empty($shop_house_no)): ?>
  <span
    class="dpd-shop-detail-line"><?php print $shop_street; ?> <?php print $shop_house_no; ?></span>
<?php endif; ?>

<?php if (!empty($shop_zip) || !empty($shop_city)): ?>
  <span
    class="dpd-shop-detail-line"><?php print $shop_zip; ?> <?php print $shop_city; ?></span>
<?php endif; ?>

<?php if (!empty($shop_country)): ?>
  <span class="dpd-shop-detail-line"><?php print $shop_country; ?></span>
<?php endif; ?>

<?php if (!empty($shop_phone)): ?>
  <span class="dpd-shop-detail-line"><?php print $shop_phone; ?></span>
<?php endif; ?>

<?php if (!empty($shop_mail)): ?>
  <span class="dpd-shop-detail-line"><?php print $shop_mail; ?></span>
<?php endif; ?>

<?php if (!empty($shop_homepage)): ?>
  <span class="dpd-shop-detail-line"><?php print $shop_homepage; ?></span>
<?php endif; ?>

<?php if (!empty($shop_opening_times)): ?>
  <div class="dpd-shop-detail-table"><?php print $shop_opening_times; ?></div>
<?php endif; ?>

<?php if (!empty($shop_select_link)): ?>
  <span class="dpd-shop-detail-line"><?php print $shop_select_link; ?></span>
<?php endif; ?>










