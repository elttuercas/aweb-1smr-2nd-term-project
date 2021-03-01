/**
 * Event handler to make an API call to delete the current message when the delete button is clicked.
 */
$(function ()
{
    let removeMessageButton : JQuery = $('#contact_messages_view_delete_message');
    removeMessageButton.on('click', function ()
    {
        $.ajax(
            {
                url     : '/api/messages/delete/' + removeMessageButton.data('hash') + '/',
                method  : 'delete',
                success : function ()
                {
                    // Redirect to the messages view.
                    window.location.href = '/contact/messages/';
                },
                error   : function ()
                {
                    // Chuck an error message in the page.
                    $().appendAlert('red', 'Se ha producido un error. Inténtelo de nuevo más tarde');
                }
            }
        );
    });
});
