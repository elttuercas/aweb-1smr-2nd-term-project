import {LoDashStatic} from "lodash";

declare var _ : LoDashStatic;

/**
 * Event listener to loop the image slider every few seconds as well as attach the event
 * listeners to allow the slides to be controlled with buttons.
 */

$(function ()
{
    // Map the slider buttons to each of the slides.
    let slides : JQuery              = $('.index_slider_slide');
    let slideControlButtons : JQuery = $('.index_slider_button');

    // Initially hide all slides but the first.
    slides.hide(0);
    slides.first().show(0);

    // Rotate the slides every 8 seconds.
    let currentSlide : number = 0;
    function startInterval()
    {
        // Ensure that the current slide does not go over the total number of slides.
        if (++currentSlide === slides.length)
        {
            currentSlide = 0;
        }

        // Fade out all slides.
        slides.hide(400);
        // Fade in the next slide.
        $(slides[currentSlide]).show(400);
        // Style the current button accordingly.
        slideControlButtons.removeClass('index_slider_button_active');
        $(slideControlButtons[currentSlide]).addClass('index_slider_button_active');
    }

    let interval : NodeJS.Timeout = setInterval(startInterval, 8000);

    _.each(slideControlButtons, function (button : HTMLElement, i : number)
    {
        // Associate each button with a slide. First with first, second with second, etc.
        $(button).on('click', function ()
        {
            slides.hide(400);
            $(slides[i]).show(400);
            slideControlButtons.removeClass('index_slider_button_active');
            $(this).addClass('index_slider_button_active');
            // Also when the button is clicked, adjust the current slide accordingly as well as reset the interval.
            clearInterval(interval);
            currentSlide = i;
            interval = setInterval(startInterval, 8000);
        });
    });
});