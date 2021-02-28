import * as $ from 'jquery';
import * as _ from 'lodash';

(<any>window).$ = $;
(<any>window)._ = _;

$.fn.extend(
    {
        /**
         * Plugin to create an alert in the page where the code is executed. The alert should only be created
         * after server-side alerts given that the function should only be called when the document has fully loaded.
         * @param alertType
         * @param alertText
         * @param altStyle
         */
        appendAlert : function (alertType : 'red' | 'yellow' | 'green', alertText : string, altStyle : boolean = true)
        {
            let alertsContainer : JQuery = $('#std_alerts_container');
            // Create the alert.
            let alertContainer : JQuery  = $('<div>')
                .addClass('std_alert_container')
                .addClass('std_alert_' + alertType + (altStyle ? '_alt' : ''));

            // Create the alert icon.
            let alertIcon : JQuery = $('<i>').addClass('uil');
            if (alertType === 'red')
            {
                alertIcon.addClass('uil-exclamation-octagon');
            }
            else if (alertType === 'yellow')
            {
                alertIcon.addClass('uil-exclamation-circle');
            }
            else
            {
                alertIcon.addClass('uil-check-circle');
            }

            // Create the alert text.
            let $alertText : JQuery = $('<div>' + alertText + '</div>').addClass('std_alert_text');

            // Create the alert close button container.
            let alertCloseBtnContainer : JQuery = $('<div>')
                .addClass('std_alert_close_container')
                .append(
                    $('<i>').addClass('uil').addClass('uil-times')
                );

            // Append all of the elements to the alert container.
            alertContainer.append(alertIcon, $alertText, alertCloseBtnContainer);
            // Append the alert container to the alerts container.
            alertsContainer.append(alertContainer);
            alertsContainer.show();
        }
    }
);

/**
 * Attach a couple of event listeners to the nav menu button for mobile view opening and closing.
 */
$(function () : void
{
    let navOpen : boolean     = false;
    let mobileNavBtn : JQuery = $('#std_header_mobile_btn').first();
    let openIcon : JQuery     = $('#std_header_open_icon');
    let closedIcon : JQuery   = $('#std_header_closed_icon');
    let navMenu : JQuery      = $('#std_nav');

    mobileNavBtn.on('click', function () : void
    {
        // After each click, set the opposite value of nav open.
        navOpen = !navOpen;
        // Show the open icon, hide the closed icon or vice versa.
        openIcon.css(
            {
                display : navOpen ? 'block' : 'none'
            }
        );
        closedIcon.css(
            {
                display : !navOpen ? 'block' : 'none'
            }
        );
        navMenu.css(
            {
                display : navOpen ? 'flex' : 'none'
            }
        );
    });
});

/**
 * Attach event listeners to the dropdown menu within the nav menu to show/hide.
 */
$(function () : void
{
    let dropdownOpen : boolean     = false;
    let dropdownButton : JQuery    = $('#std_nav_dropdown_button');
    let dropdownIcon : JQuery      = $('#std_nav_dropdown_button_icon');
    let dropdownContainer : JQuery = $('#std_nav_dropdown_container');

    dropdownButton.on('click', function (evt : JQuery.ClickEvent) : void
    {
        evt.stopPropagation();
        dropdownOpen = !dropdownOpen;
        dropdownContainer.css(
            {
                display : dropdownOpen ? 'flex' : 'none'
            }
        );
        dropdownIcon.css(
            {
                '--tw-rotate' : dropdownOpen ? '180deg' : '0deg'
            }
        );
    });

    // Clicks outside of the dropdown when it is open, should close the dropdown.
    $(window).on('click', function ()
    {
        if (dropdownOpen)
        {
            dropdownContainer.css(
                {
                    display : 'none',
                }
            );
            dropdownIcon.css(
                {
                    '--tw-rotate' : '0deg'
                }
            );
            dropdownOpen = false;
        }
    });
});

/**
 * Event listener to mark a nav link as active if the href attribute matches the current window path.
 */
$(function ()
{
    let navLinks : JQuery = $('#std_nav').children('a');
    _.each(navLinks, function (navLink : HTMLElement)
    {
        let $navLink : JQuery = $(navLink);
        if (window.location.pathname === $navLink.attr('href'))
        {
            $navLink.addClass('std_nav_current_link');
            return false;
        }
    });
});

/**
 * Event listener to remove the alerts when the close button is clicked.
 */
$(document).on('click', '.std_alert_close_container', function ()
{
    $(this).parents('.std_alert_container').remove();
    // Check whether there are alerts left in the container. If not, hide it.
    let alertsContainer : JQuery = $(this).parents('#std_alerts_container');
    if (alertsContainer.children().length === 0)
    {
        alertsContainer.hide();
    }
});

/**
 * Event listener to hide the alerts container div when it has no children. This could be done with CSS using the
 * pseudo-element selector :empty but it only works when there is nothing between the tags or only an HTML comment.
 * Since the div is generated with drogon templates, there are more than a few spaces so it is never targeted by :empty.
 */
$(function ()
{
    let alertsContainer : JQuery = $('#std_alerts_container');
    if (alertsContainer.children().length === 0)
    {
        alertsContainer.hide();
    }
});
