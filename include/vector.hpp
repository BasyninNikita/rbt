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
	
	bool find(T value) const
	    {
		if (root_ == nullptr)
		{
		    return false;
		}
		else
		{
		    node_t* node = root_;
		    while (node != nullptr)
		    {
			if (node->value == value) return true;
			else if (node->value < value) node = node->right;
			else if (node->value > value) node = node->left;
		    }
		    return false;
		}
	    }
