$(function() {
    // SETUP
    var $list, $newItemForm;
    var editing = 0;
    var item = '';                                 // item is an empty string
    $list = $('#toDo');                               // Cache the unordered list
    $newItemForm = $('#newItemForm');              // Cache form to add new items

    // ADDING A NEW LIST ITEM
    $newItemForm.on('submit', function(e) {       // When a new item is submitted
        e.preventDefault();                         // Prevent form being submitted
        var text = $('input:text').val();           // Get value of text input
        $list.append('<li class=\"incomplete\" >' + text +  '</li>');      // Add item to end of the list
        $('input:text').val('');                    // Empty the text input
    });

  // When a list item is clicked a single time, it will toggle between complete and incomplete
    $list.on('click', 'li', function() {
    /*var $this = $(this);               // Cache the element in a jQuery object
    var complete = $this.hasClass('complete');  // Is item complete */
        //This if statement is a workaound to a problem I encountered later on in the code
        if (editing === 0){
            $(this).toggleClass("complete incomplete");
        }
    });
    
    //My failed attempt at using double-click-to-edit functionality. The $list.append in $newItemForm.on() was much longer to give each li display and edit tags.
    //One problem was that when I doubleclicked, it would trigger two single click events instead. My workaround was to simply use right-click/contextmenu instead of dblclick
    //The other problem was that, in order to make this work, I needed to include a hidden form in each li. This broke newItemForm after a single li was created.
    //I suspect this was because $('input:text').val() began trying to take input from the first li when trying to create the second li, but I am not sure.
    /* $(".display").dblclick(function(){
        $(this).hide().siblings(".edit").show().val($(this).text()).focus();
    });

    $(".edit").focusout(function(){
        $(this).hide().siblings(".display").show().text($(this).val());
    }); */
    
    //When the user right-clicks on an item in the list, they are able to edit it
    $list.on('contextmenu', 'li', function(e) {
        e.preventDefault();
        
        //I tried to use focus() at several places to force focus onto the new text field, but I could not get it to work, so I created this variable as a workaround.
        //It prevents the toggleClass from triggering when the user clicks on the text field so that they are able to edit. If the toggleClass triggers, the text field to edit disappears
        editing = 1; 
        var that = $(this);
        if (that.find('input').length > 0) {
            return;
        }
        var currentText = that.text();
        
        var $input = $('<input>').val(currentText);
        
        $(this).append($input);
        
        $(document).click(function(event) {
            if(!$(event.target).closest('li').length) {
                if ($input.val()) {
                    that.text($input.val());
                }
                that.find('input').remove();
            }
            editing = 0; //Allows the toggleClass to work again after editing is complete
        });
    });
    
    $('#remove').on('click', function() {
        $(".complete").remove();
    });

});