function bst_left_print(root) {
    var max_printed_level = -1;

    function bst_left_print_closure(root, level) {
        level = level || 0;

        if (level > max_printed_level) {
            console.log("level: " + level + " - " + root.value);
            max_printed_level = level;
        }

        if (root.left) {
            bst_left_print_closure(root.left, level+1);
        }
        if (root.right) {
            bst_left_print_closure(root.right, level+1);
        }
    }

    bst_left_print_closure(root);
}

function bst_right_print(root) {
    var max_printed_level = -1;

    function bst_right_print_closure(root, level) {
        level = level || 0;

        if (level > max_printed_level) {
            console.log("level: " + level + " - " + root.value);
            max_printed_level = level;
        }

        if (root.right) {
            bst_right_print_closure(root.right, level+1);
        }
        if (root.left) {
            bst_right_print_closure(root.left, level+1);
        }
    }

    bst_right_print_closure(root);
}

function make_node(val, left_child, right_child) {
    return {
        value   : val,
        left    : left_child,
        right   : right_child
    };
}

var r;
r = make_node(12,
        make_node(21,
            make_node(33,
                null,
                make_node(44,
                    null,
                    null
                )
            )
        ),
        make_node(1,
            make_node(4,
                null,
                null
            ),
            make_node(5,
                null,
                make_node(8,
                    null,
                    make_node(9,
                        null,
                        null
                    )
                )
            )
        )
    );

console.log("*** LEFT PRINT ***");
bst_left_print(r);
console.log("*** RIGHT PRINT ***");
bst_right_print(r);
