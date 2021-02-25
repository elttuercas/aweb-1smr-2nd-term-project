/**
 * Attach a couple of event handlers to the form fields as validation prior to submission.
 */
$(function ()
{
    // All of the required fields in the contact form.
    let requiredFields : JQuery = $('#input_name, #input_surname, #input_email, #textarea_message');
    _.each(requiredFields, function (field : HTMLElement) : void
    {
        let $field = $(field);
        $field.on('change', function ()
        {
            /*
             * Technically a cast to string however, the return value is already a string. ¯\_(ツ)_/¯
             * This simply serves to stop the TypeScript compiler from complaining.
             */
            if ((<string>$field.val()).length !== 0)
            {
                $field.addClass('contact_form_field_input_valid');
                $field.removeClass('contact_form_field_input_error');
            }
            else
            {
                $field.addClass('contact_form_field_input_error');
                $field.removeClass('contact_form_field_input_valid');
            }
        });
    });

    // Extra check for the email field.
    let emailField : JQuery   = $('#input_email');
    const emailRegEx : RegExp = new RegExp(/(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)])/, 'i');
    emailField.on('change', function ()
    {
        // Compare the value of the email field with the RegEx.
        if ((<string>emailField.val()).match(emailRegEx))
        {
            emailField.addClass('contact_form_field_input_valid');
            emailField.removeClass('contact_form_field_input_error');
        }
        else
        {
            emailField.addClass('contact_form_field_input_error');
            emailField.removeClass('contact_form_field_input_valid');
        }
    });

    // Override default form submission button.
    let contactForm : JQuery = $('#contact_form');
    contactForm.on('submit', function (evt : JQuery.SubmitEvent) : void
    {
        // Check that there are no form elements without the valid class. If there are, prevent the form submission.
        if ($('.contact_form_field_input_valid').length !== 4)
        {
            evt.preventDefault();
        }
    });
});
