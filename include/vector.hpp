#include <iostream>
#include <algorithm>
#include <cassert>
template <typename T>
class tree_t
{
private:
	struct node_t{
		node_t * left;
		node_t * right;
		node_t * parent;
		T value;
		bool color;
	};
public:
	tree_t(){
		root_=nullptr;
	}
	~tree_t(){
		destr(root_);
	}
	void destr(node_t* node) {
    		if(node != nullptr)
    		{
     			destr(node->left);
     			destr(node->right);
			delete node;
    		}
  	}
	void print(std::ostream & stream,int lvl,node_t* node){
	if (node==nullptr)
		return;
		print(stream,lvl +1,node->right);
			for (unsigned int i = 0; i < lvl; i++) {
			stream << "---";
		}
		stream << node->value <<std::endl;
		print(stream, lvl + 1, node->left);
	}
	bool  ravnbranch(node_t * first,node_t * second) const{
		if((first==nullptr) && (second==nullptr)) return (true);
		else if (first!=nullptr && second!=nullptr){
				if((first->value==second->value)&&(ravnbranch(first->left,second->left)) && (ravnbranch(first->right,second->right)))
					{return(true);}
				else return(false);
		}
		else return(false);
	}
	auto operator==(tree_t & other) const{
		node_t * first;
		node_t * second;
        	first = root_;
        	second= other.root();
        	return(ravnbranch(first, second));
	}
	tree_t(std::initializer_list<T> keys){
		root_=nullptr;
		int n = keys.size();
		const int* _ptr = keys.begin();
		for (int i=0; i < n; i++)
		{
			insert(_ptr[i]);
		}
	}
	 node_t* root() const
    	{
        	return root_;
    	}
	bool find(T value) const{
	node_t * node=root_;
	while(node!=nullptr){
		if (value==node->value)
			return true;
		else {
			if (value<node->value){
				node=node->left;	
			}
			else node=node->right;
		}
	}
	return false;
	}
	void  oper1(char op, T value){
	if(op=='+')
	{
		insert(value);
	}
	
	else if(op=='q')
	{
		exit(0);
	}
	else std::cout<<"incorrect operation";	
	}
	void oper2(char op, T value,std::ostream& stream){
		if(op=='?')
		{
			if(find(value))
			\	stream<<"true";
			else stream<<"false";
			
		}
		else if(op=='=')
		{
			print(stream,0,root_);
		}
		else std::cout<<"incorrect operation";	
		}
	 node_t * gparent(node_t * node){
		if(node!= nullptr && node->parent != nullptr){
		    return node->parent->parent;
		}
		else return nullptr;
	    }

	    node_t * uncle(node_t * node){
		node_t * gparent = gparent(node);
		if(gparent == nullptr) return nullptr;
		if(node->parent == gparent->left) return gparent->right;
		else return gparent->left;
	    }
	void rotate_right(node_t * node){
        	node_t * newnode = node->left;
        	newnode->parent = node->parent;
        	if(node->parent != nullptr){
        	    if(node->parent->left == node){
        	        node->parent->left = newnode;
        	    }
        	    else node->parent->right = newnode;
        	}
        	node->left = newnode->right;
        	if(newnode->right != nullptr){
        	    newnode->right->parent = node;
        	}	
        	if(node->parent == nullptr) root_ = newnode;
        	node->parent = newnode;
        	newnode->right = node;
    	}
	void rotate_left(node_t * node){
        node_t * newnode = node->right;
        newnode->parent = node->parent;
        if(node->parent != nullptr){
            if(node->parent->left == node){
                node->parent->left = newnode;
            }
            else node->parent->right = newnode;
        }
        node->right = newnode->left;
        if(newnode->left != nullptr){
            newnode->left->parent = node;
        }
        if(node->parent == nullptr) root_ = newnode;
        node->parent = newnode;
        newnode->left = node;
    }
    
    
