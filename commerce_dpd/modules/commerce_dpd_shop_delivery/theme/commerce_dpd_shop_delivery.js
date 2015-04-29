(function ($) {
    Drupal.behaviors.commerceDPDShopDelivery = {
        attach: function (context, settings) {


            if (!$('.commerce-dpd-shop-delivery-custom-address-street').val()) {

                if ($('.commerce-dpd-shop-delivery-shop-option:checked').val()) {
                    $('.dpd-shop-fieldset').addClass('collapsed collapse-processed');
                } else {
                    $('.dpd-shop-fieldset').removeClass('collapsed collapse-processed');
                }


            }


        }
    };

})(jQuery);
