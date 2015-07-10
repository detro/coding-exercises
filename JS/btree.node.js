function make_btree_node(_degree, _isLeaf) {
    const MAX_KEYS    = 2 * _degree -1; //=> MAX_CHILDS = 2 * _degree;

    var _keys       = [],
        _childs     = [];

    if (typeof(_isLeaf) === "undefined") _isLeaf = true;

    function _isFull() {
        return this.getKeysAmount() === MAX_KEYS;
    }

    function _traverse(depth) {
        var i, ilen,
            prefix;

        // normalize "depth"
        depth = depth || 0;
        // prepare prefix to use while printing at this "depth" of the tree
        prefix = Array(depth*3 +1).join(' ');

        // Begin node traverse
        console.log(prefix + "[");

        for (i = 0, ilen = this.getKeysAmount(); i < ilen; ++i) {
            // If this is not a Leaf, traverse towards the child
            if (!this.isLeaf()) this.getChild(i).traverse(depth +1);

            console.log(prefix + ' ' + this.getKey(i));
        }
        // If this is not a Leaf, traverse towards the child
        if (!this.isLeaf()) this.getChild(i).traverse(depth +1);

        // End node traverse
        console.log(prefix + "]");
    }

    function _search(key) {
        var i = 0,
            keysAmount = this.getKeysAmount();

        // look for the first key "smaller or equal" than "key"
        while (i < keysAmount && key > this.getKey(i))
            ++i;

        // If this very node contains "key", return this node
        if (this.getKey(i) === key)
            return this;

        // If this node is a leaf, the search was unsuccessful
        if (this.isLeaf())
            return null;

        // Continue search downward
        return this.getChild(i).search(key);
    }

    function _insertIfNotFull(key) {
        var i;

        // If this is full, insertion failed
        if (this.isFull()) return false;

        // Start from the right-most key
        i =  this.getKeysAmount() - 1;

        // If this is a leaf, we will put the key here (keeping height constant)
        if (this.isLeaf()) {
            // Find right location for the new key:
            // keep moving current keys to the right until the right spot is found
            while (i >= 0 && this.getKey(i) > key) {
                this.setKey(i + 1, this.getKey(i));
                --i;
            }

            // Insert the key at the right spot, now that it has been found
            this.setKey(i + 1, key);
        } else {
            // Find right child that will contain the new key
            while (i >= 0 && this.getKey(i) > key) --i;

            // If child is full
            if (this.getChild(i + 1).isFull()) {
                // Split the child (because it's full)
                this.splitChildIfFull(i + 1, this.getChild(i + 1));

                // After splitting, the middle key in the child
                // is stored in the parent.
                // We need to decide which of the 2 new childs will
                // contain the new key: the one
                // in "i+1" (left new child) or "i+1+1" (right new child).
                if (this.getKey(i + 1) < key) ++i;
            }

            // Now we insert (recursively) in the child
            this.getChild(i + 1).insertIfNotFull(key);
        }

        // insertion succeeded
        return true;
    }

    function _splitChildIfFull(child_idx, child) {
        var new_node,
            j, jlen;

        // If the child is not full, split failed
        if (!child.isFull()) return false;

        // Create new node that will store "degree -1" keys of "child"
        new_node = make_btree_node(this.getDegree(), child.isLeaf());

        // Move the last "degree -1" keys from "child" to "new_node"
        for (j = 0, jlen = this.getDegree() -1; j < jlen; ++j) new_node.setKey(j, child.getKey(j + this.getDegree()));
        child.dropKeys(this.getDegree() -1);

        // If "child" is not a leaf, move the last "degree" childs from "child" to "new_node"
        if (!child.isLeaf()) {
            for (j = 0, jlen = this.getDegree(); j < jlen; ++j) new_node.setChild(j, child.getChild(j + this.getDegree()));
            // child.dropChilds(this.getDegree());
        }

        // We will add a new child to "this" node: we must make up space for it
        for (j = this.getKeysAmount(); j >= child_idx +1; --j) this.setChild(j + 1, this.getChild(j));

        // Add "new_node" as child
        this.setChild(child_idx +1, new_node);

        // We will move a key in "this" node: we must make up space for it
        for (j = this.getKeysAmount() -1; j >= child_idx; --j) this.setKey(j + 1, this.getKey(j));

        // Move middle key from "child" to "this" node
        this.setKey(child_idx, child.getKey(this.getDegree() -1));
        child.dropKeys(1);
    }

    return {
        getKeys         : function() { return _keys; },
        getKey          : function(idx) { return _keys.length > idx ? _keys[idx] : null },
        getKeysAmount   : function() { return _keys.length },
        setKey          : function(idx, key) { _keys[idx] = key; },
        dropKeys        : function(amount) { _keys = _keys.slice(0, _keys.length - amount); },

        getChilds       : function() { return _childs; },
        getChild        : function(idx) { return _childs.length > idx ? _childs[idx] : null },
        getChildsAmount : function() { return _childs.length; },
        setChild        : function(idx, child) { _childs[idx] = child; },

        isLeaf          : function() { return _isLeaf; },
        getDegree       : function() { return _degree; },

        isFull          : _isFull,
        traverse        : _traverse,
        search          : _search,
        insertIfNotFull : _insertIfNotFull,
        splitChildIfFull: _splitChildIfFull
    };
}

function make_btree(_degree) {
    var
        _root = null;

    function _traverse() {
        if (_root !== null) {
            _root.traverse();
        }
    }

    function _search(key) {
        return _root === null ? null : _root.search(key);
    }

    function _insert(key) {
        var new_root,
            i;

        // If tree is empty, we create a new root
        if (_root === null) {
            _root = make_btree_node(this.getDegree(), true);
        }

        // If root is full, tree has to grow in height:
        // we will split the root, create a new root and set it as parent
        // of the 2 childs that came out of the split.
        if (_root.isFull()) {
            // Create a new root, knowing that will NOT be a leaf
            new_root = make_btree_node(this.getDegree(), false);

            // Make current root first child of the new root
            new_root.setChild(0, _root);
            // Split the old root and move 1 key up
            new_root.splitChildIfFull(0, _root);

            // Figure out which of the 2 childs of the new root will get the key
            if (new_root.getKey(0) < key) {
                new_root.getChild(1).insertIfNotFull(key);
            } else {
                new_root.getChild(0).insertIfNotFull(key);
            }

            // Change root
            _root = new_root;
        } else {
            // root is not full: we can just insert the new key
            _root.insertIfNotFull(key);
        }
    }

    return {
        getDegree       : function() { return _degree; },

        traverse        : _traverse,
        search          : _search,
        insert          : _insert
    }
}

var t = make_btree(3),
    input = [],
    input_size = 50,
    i;

for (i = 0; i < input_size; ++i) {
    input.push( Math.floor( Math.random() * 1000 ) );
}

for (i = 0; i < input_size; ++i) {
    t.insert(input[i]);
}

console.log("*** INPUT: " + input);

console.log("*** TRAVERSAL:");
t.traverse();

console.log("------------------");

var needle = input[ Math.floor(Math.random() * input_size) % input_size ],
    n = t.search(needle);
if (n !== null) {
    console.log("needle: "+ needle);
    console.log(n.getKeysAmount());
    console.log(n.getKeys());
    console.log(n.getChildsAmount());
}

