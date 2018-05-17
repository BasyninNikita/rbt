#include <iostream>
#include <algorithm>
#include <cassert>
template <typename T>
class tree_t
{
private:
    struct node_t
    {
        node_t* left;
        node_t* right;
        node_t* parent;
        T value;
        bool color;
    };

private:
    node_t* root_;

public:
    tree_t()
    {
        root_ = nullptr;
    }
    ~tree_t()
    {
        destr(root_);
    }
    void destr(node_t* node)
    {
        if (node)
        {
            destr(node->left);
            destr(node->right);
            delete node;
        }
    }
    void print(std::ostream& stream, int lvl, node_t* node)
    {
        if (!node)
            return;
        print(stream, lvl + 1, node->right);
        for (unsigned int i = 0; i < lvl; i++)
        {
            stream << "---";
        }
        stream << node->value << std::endl;
        print(stream, lvl + 1, node->left);
    }
    bool ravnbranch(node_t* first, node_t* second) const
    {
        if (!first && !second)
            return (true);
        else if (first  && second )
        {
            if ((first->value == second->value) && (ravnbranch(first->left, second->left))
                && (ravnbranch(first->right, second->right)))
            {
                return (true);
            }
            else
                return (false);
        }
        else
            return (false);
    }
    auto operator==(tree_t const & other) const
    {
        node_t* first = root_;
        node_t* second= other.root();
        return (ravnbranch(first, second));
    }
    
    tree_t(std::initializer_list<T> keys)
    {
        root_ = nullptr;
        //int n = keys.size();
        //const int* _ptr = keys.begin();
        for (auto i = keys.begin(); i < keys.end(); i++)
        {
            insert(i);
        }
    }
    node_t* root() const
    {
        return root_;
    }
    bool find(T value) const
    {
        node_t* node = root_;
        while (node)
        {
            if (value == node->value)
                return true;
            else
            {
                value < node->value ? node = node->left : node=node->right;
               /* if (value < node->value)
                {
                    node = node->left;
                }
                else
                    node = node->right;*/
            }
        }
        return false;
    }
    void oper1(char op, T value)
    {
        if (op == '+')
        {
            insert(value);
        }

        else if (op == 'q')
        {
            exit(0);
        }
        else
            std::cout << "incorrect operation";
    }
    void oper2(char op, T value, std::ostream& stream)
    {
        if (op == '?')
        {
            if (find(value))
                stream << "true";
            else
                stream << "false";
        }
        else if (op == '=')
        {
            print(stream, 0, root_);
        }
        else
            std::cout << "incorrect operation";
    }
    node_t* gparent(node_t* node) const
    {
        node_t * n;
        (node && node->parent) ? n= node->parent->parent :  n= nullptr;
        return n;
        /*if (node && node->parent)
        {
            return node->parent->parent;
        }
        else
            return nullptr;*/
    }
    node_t* uncle(node_t* node) const
    {
        node_t* gp = gparent(node);
        if (!gp )
            return nullptr;
        if (node->parent == gp->left)
            return gp->right;
        else
            return gp->left;
    }
    void rotate_right(node_t* node)
    {
        node_t* newnode = node->left;
        newnode->parent = node->parent;
        if (node->parent)
        {
            if (node->parent->left == node)
            {
                node->parent->left = newnode;
            }
            else
                node->parent->right = newnode;
        }
        node->left = newnode->right;
        if (newnode->right)
        {
            newnode->right->parent = node;
        }
        if (!node->parent)
            root_ = newnode;
        node->parent = newnode;
        newnode->right = node;
    }
    void rotate_left(node_t* node)
    {
        node_t* newnode = node->right;
        newnode->parent = node->parent;
        if (node->parent)
        {
            if (node->parent->left == node)
            {
                node->parent->left = newnode;
            }
            else
                node->parent->right = newnode;
        }
        node->right = newnode->left;
        if (newnode->left)
        {
            newnode->left->parent = node;
        }
        if (!node->parent )
            root_ = newnode;
        node->parent = newnode;
        newnode->left = node;
    }
    void insert(T value)
    {
        node_t * node=new node_t;
        node->value = value;
        node->left = nullptr;
        node->right = nullptr;
        if (!root_ )
        {
            node->parent = nullptr;
            node->color = false;
            root_ = node;
        }
        else
        {
            node_t* branch = root_;
            while (branch)
            {
                if (value < branch->value)
                {
                    if (!branch->left )
                    {
                        branch->left = node;
                        node->parent=branch;
                        insert_case1(node);
                        return;
                    }
                    else
                    {
                        branch = branch->left;
                    }
                }
                else if (value >= branch->value)
                {
                    if (!branch->right)
                    {
                        branch->right = node;
                        node->parent=branch;
                        insert_case1(node);
                        return;
                    }
                    else
                    {
                        branch = branch->right;
                    }
                }
            }
        }
    }
    void insert_case1(node_t* node)
    {
        if (!node->parent)
            node->color = false;
        else
            insert_case2(node);
    }

    void insert_case2(node_t* node)
    {
        if (node->parent->color == false)
            return;
        else
            insert_case3(node);
    }

    void insert_case3(node_t* node)
    {
        node_t* unc = uncle(node);
        node_t* gp;
        if (unc  && unc->color == true)
        {
            node->parent->color = false;
            unc->color = false;
            gp = gparent(node);
            gp->color = true;
            insert_case1(gp);
        }
        else
            insert_case4(node);
    }

    void insert_case4(node_t* node)
    {
        node_t* gp = gparent(node);
        if (node == node->parent->right && node->parent == gp->left)
        {
            rotate_left(node->parent);
            node = node->left;
        }
        else if (node == node->parent->left && node->parent == gp->right)
        {
            rotate_right(node->parent);
            node = node->right;
        }
        insert_case5(node);
    }

    void insert_case5(node_t* node)
    {
        node_t* gp = gparent(node);
        node->parent->color = false;
        gp->color = true;
        if (node == node->parent->left && gp->left == node->parent)
            rotate_right(gp);
        else
            rotate_left(gp);
    }
    bool remove(T value)
    {
        if (!root_)
        {
            return false;
        }
        else
        {
            node_t* param1 = nullptr;
            node_t* param2 = root_;
            while (1)
            {
                if (param2->value == value)
                {
                    break;
                }
                else if (value > param2->value)
                {
                    param1 = param2;
                    param2 = param2->right;
                }
                else if (value < param2->value)
                {
                    param1 = param2;
                    param2 = param2->left;
                }
                if (!param2)
                {
                    return false;
                }
            }
            if (!param2->left && !param2->right)
            {
                if (param2 == root_)
                {
                    node_t* node = root_;
                    root_ = nullptr;
                    delete node;
                }
                else
                {
                    if (param1->left == param2)
                    {
                        if (param2->color == false)
                            delete_case1(param2);
                        if (param2->parent->left == param2)
                            param2->parent->left = nullptr;
                        else if (param2->parent->right == param2)
                            param2->parent->right = nullptr;
                        delete param2;
                    }
                    if (param1->right == param2)
                    {
                        if (param2->color == false)
                            delete_case1(param2);
                        if (param2->parent->left == param2)
                            param2->parent->left = nullptr;
                        else if (param2->parent->right == param2)
                            param2->parent->right = nullptr;
                        delete param2;
                    }
                }
            }
            else if ((param2->left  && !param2->right == nullptr)
                || (!param2->left && param2->right ))
            {
                if (param2 == root_)
                {
                    node_t* node = root_;
                    if (param2->left )
                    {
                        root_ = param2->left;
                        root_->parent = nullptr;
                    }
                    else if (param2->right)
                    {
                        root_ = param2->right;
                        root_->parent = nullptr;
                    }
                    delete node;
                }
                else
                {
                    if (param1->left == param2)
                    {
                        if (param2->left)
                        {
                            param1->left = param2->left;
                            param2->left->parent = param1;
                            if (param2->color == false)
                            {
                                if (param1->left->color == true)
                                    param1->left->color = false;
                                else
                                    delete_case1(param1->left);
                            }
                            delete param2;
                        }
                        else if (param2->right)
                        {
                            param1->left = param2->right;
                            param2->right->parent = param1;
                            if (param2->color == false)
                            {
                                if (param1->left->color == true)
                                    param1->left->color = false;
                                else
                                    delete_case1(param1->left);
                            }
                            delete param2;
                        }
                    }
                    else if (param1->right == param2)
                    {
                        if (param2->left)
                        {
                            param1->right = param2->left;
                            param2->left->parent = param1;
                            if (param2->color == false)
                            {
                                if (param1->right->color == true)
                                    param1->right->color = false;
                                else
                                    delete_case1(param1->right);
                            }
                            delete param2;
                        }
                        else if (param2->right )
                        {
                            param1->right = param2->right;
                            param2->right->parent = param1;
                            if (param2->color == false)
                            {
                                if (param1->right->color == true)
                                    param1->right->color = false;
                                else
                                    delete_case1(param1->right);
                            }
                            delete param2;
                        }
                    }
                }
            }
            else if (param2->left && param2->right)
            {
                node_t* node = param2;
                param1 = param2;
                param2 = param2->right;
                if (!param2->left )
                {
                    if (!param2->right)
                    {
                        bool ncol = node->color;
                        node->value = param2->value;
                        node->color = param2->color;
                        node->right = nullptr;
                        delete param2;
                        if (ncol == false)
                        {
                            if (node->color == true)
                                node->color = false;
                            else
                                delete_case1(node);
                        }
                    }
                    else
                    {
                        bool ncol = node->color;
                        node->value = param2->value;
                        node->color = param2->color;
                        node->right = param2->right;
                        param2->right->parent = node;
                        delete param2;
                        if (ncol == false)
                        {
                            if (node->color == true)
                                node->color = false;
                            else
                                delete_case1(node);
                        }
                    }
                }
                else
                {
                    while (param2->left)
                    {
                        param1 = param2;
                        param2 = param2->left;
                    }
                    if (!param2->right )
                    {
                        bool ncol = node->color;
                        node->value = param2->value;
                        node->color = param2->color;
                        param1->left = nullptr;
                        delete param2;
                        if (ncol == false)
                        {
                            if (node->color == true)
                                node->color = false;
                            else
                                delete_case1(node);
                        }
                    }
                    else
                    {
                        bool ncol = node->color;
                        node->value = param2->value;
                        node->color = param2->color;
                        param1->left = param2->right;
                        param2->right->parent = param1;
                        delete param2;
                        if (ncol == false)
                        {
                            if (node->color == true)
                                node->color = false;
                            else
                                delete_case1(node);
                        }
                    }
                }
            }
            return true;
        }
    }

    node_t* sibling(node_t* n)
    {
        if (n == n->parent->left)
            return n->parent->right;
        else
            return n->parent->left;
    }

    void delete_case1(node_t* n)
    {
        if (n->parent)
            delete_case2(n);
    }

    void delete_case2(node_t* n)
    {
        node_t* s = sibling(n);
        if (!s)
            return;
        if (s->color == true)
        {
            n->parent->color = true;
            s->color = false;
            if (n == n->parent->left)
                rotate_left(n->parent);
            else
                rotate_right(n->parent);
        }
        delete_case3(n);
    }

    void delete_case3(node_t* n)
    {
        node_t* s = sibling(n);
        if (!s->left  || !s->right)
            return;
        if ((n->parent->color == false) && (s->color == false) && (s->left->color == false)
            && (s->right->color == false))
        {
            s->color = true;
            delete_case1(n->parent);
        }
        else
            delete_case4(n);
    }

    void delete_case4(node_t* n)
    {
        node_t* s = sibling(n);
        if ((n->parent->color == true) && (s->color == false) && (s->left->color == false)
            && (s->right->color == false))
        {
            s->color = true;
            n->parent->color = false;
        }
        else
            delete_case5(n);
    }

    void delete_case5(node_t* n)
    {
        node_t* s = sibling(n);
        if (s->color == false)
        {
            if ((n == n->parent->left) && (s->right->color == false) && (s->left->color == true))
            {
                s->color = true;
                s->left->color = false;
                rotate_right(s);
            }
            else if ((n == n->parent->right) && (s->left->color == false)
                && (s->right->color == true))
            {
                s->color = true;
                s->right->color = false;
                rotate_left(s);
            }
        }
        delete_case6(n);
    }

    void delete_case6(node_t* n)
    {
        node_t* s = sibling(n);
        s->color = n->parent->color;
        n->parent->color = false;
        if (n == n->parent->left)
        {
            s->right->color = false;
            rotate_left(n->parent);
        }
        else
        {
            s->left->color = false;
            rotate_right(n->parent);
        }
    }
};
