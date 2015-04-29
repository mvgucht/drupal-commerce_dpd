<?php
/**
 * @file
 * Commerce DPD Parcel Life Cycle
 *
 * Available variables:
 * - $parcel_number : The Parcel Number
 * - $service_label: The Label for the selected service
 * - $service: The Service
 * - $states: The shipment states
 *
 * @see template_preprocess_commerce_dpd_parcel_life_cycle()
 */
?>

<h4><?php print $shipment_parcel_number_label; ?>
  : <?php print $shipment_parcel_number; ?></h4>

<div class="commerce-dpd-parcel-life-cycle-service-label">
  <strong><?php print $shipment_service_label; ?></strong></div>
<div
  class="commerce-dpd-parcel-life-cycle-service"><?php print $shipment_service_value; ?></div>

<div class="commerce-dpd-parcel-life-cycle-states">
  <strong><?php print $shipment_states_label; ?></strong>:
  <?php print $shipment_states; ?>
</div>

