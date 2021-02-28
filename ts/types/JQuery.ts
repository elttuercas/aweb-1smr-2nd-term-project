/**
 * Interface JQueryStatic.
 *
 * This interface exists to provide code completion for the plugins defined in userland code.
 *
 * @author Carlos Amores
 */
interface JQuery
{
    appendAlert : (alertType : 'red' | 'yellow' | 'green', alertText : string, altStyle ? : boolean) => void
}
