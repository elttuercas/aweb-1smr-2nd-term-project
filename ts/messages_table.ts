import ContactMessage from "./types/ContactMessage";
import * as _         from "lodash";

/**
 * This function serves to update the messages table with the values sent by API.
 */
function updateTableValues(apiData : Array<ContactMessage>)
{
    let messagesTable : JQuery = $('#contact_messages_table');
    // Remove all table rows so they may be replaced with the API data.
    messagesTable.find('tr').remove();

    if (apiData.length > 0)
    {
        _.each(apiData, function (datum : ContactMessage)
        {
            let newHeadTr = $('<tr>');
            // Add th elements to the thead row.
            newHeadTr.append(
                $('<th>Fecha</th>'),
                $('<th>Nombre</th>'),
                $('<th>Apellidos</th>'),
                $('<th>Email</th>'),
                $('<th></th>'),
            );
            // Append the row to the thead.
            messagesTable.children('thead').append(newHeadTr);

            // Calculate the date of the message in YYYY-mm-dd format.
            let messageDate : Date = new Date(datum.submission_ts * 1000);
            let year : string      = String(messageDate.getUTCFullYear());
            let month : string     = String(messageDate.getUTCMonth() + 1);
            let day : string       = String(messageDate.getUTCDate());

            if (month.length < 2)
            {
                month = '0' + month;
            }
            if (day.length < 2)
            {
                day = '0' + day;
            }

            let formattedDate : string = [year, month, day].join('-');

            let newBodyTr = $('<tr>');
            // Append the object data to the row.
            newBodyTr.append(
                $('<td>' + formattedDate + '</td>'),
                $('<td>' + datum.name + '</td>'),
                $('<td>' + datum.surname + '</td>'),
                $('<td>' + datum.email + '</td>'),
                $('<td><a href="/contact/messages/view/' + datum.hash + '/">VER</a></td>'),
            );
            // Append the new row to the table.
            messagesTable.children('tbody').append(newBodyTr);
        });
    }
    else
    {
        let newHeadTr = $('<tr>');
        newHeadTr.append(
            $('<th>Fecha</th>'),
            $('<th>Nombre</th>'),
            $('<th>Apellidos</th>'),
            $('<th>Email</th>'),
            $('<th></th>'),
        );
        messagesTable.children('thead').append(newHeadTr);
    }
}

/**
 * Function to send a request to the API when the search fields are altered in some form.
 */
function sendApiRequest()
{
    let searchInput : JQuery    = $('#contact_messages_table_search_input');
    let searchModifier : JQuery = $('#contact_messages_table_search_modifier');

    /*
     * Take the current value of the input and modifier. Again, technically a cast so TS does not complain but the
     * value can only be a string.
     */
    let query : string     = <string>searchInput.val();
    let queryType : string = <string>searchModifier.val();

    // Only send a request if there is some value in the query field.
    if (query.length > 0)
    {
        $.ajax({
                url      : '/api/messages/',
                type     : 'get',
                data     : {
                    q  : query,
                    qt : queryType
                },
                dataType : 'json',
                success  : updateTableValues,
                error    : function (jqXHR : JQuery.jqXHR)
                {
                    // TODO: Show error message
                }
            }
        );
    }
}

/**
 * Create an event handler which sends a request to the backend to update the table whenever the search field
 * is changed.
 */
$(function ()
{
    let searchInput : JQuery    = $('#contact_messages_table_search_input');
    let searchModifier : JQuery = $('#contact_messages_table_search_modifier');

    // The request to the API should be made when either input or search modifiers are changed.
    searchInput.on('input', sendApiRequest);
    searchModifier.on('change', sendApiRequest);
});
