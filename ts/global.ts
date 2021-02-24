import * as $ from 'jquery';
import * as _ from 'lodash';

/**
 * Attach a couple of event listeners to the nav menu button for mobile view opening and closing.
 */
$(function () : void
{
    let navOpen : boolean = false;
    let mobileNavBtn : JQuery = $('#std_header_mobile_btn').first();
    let openIcon : JQuery = $('#std_header_open_icon');
    let closedIcon : JQuery = $('#std_header_closed_icon');
    let navMenu : JQuery = $('#std_nav');

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
    let dropdownOpen : boolean = false;
    let dropdownButton : JQuery = $('#std_nav_dropdown_button');
    let dropdownIcon : JQuery = $('#std_nav_dropdown_button_icon');
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
