// Æ½ºâ¶þ²æÊ÷ 

#include <iostream>
using namespace std;

#ifndef BSTREE
#define BSTREE 

template<typename T, typename KEY>
struct BSTNode
{
	KEY key;
	T data;
	int bf;
	BSTNode* lc;
	BSTNode* rc;
};

template<typename T, typename KEY>
class BSTree
{
public:
	BSTree() { __bst = NULL; }
	
	void init() { Destroy(); __bst = NULL; }
	
	int Insert(KEY key, T val) { int taller = 0; return _Insert(__bst, key, val, taller); }
	
	int Delete(KEY key) { int lower = 0; return _Delete(__bst, key, lower); }
	
	bool Find(KEY key, T &val) { return _Find(__bst, key, val); }
	
	void Destroy() { _Destroy(__bst); }
	
	~BSTree() { Destroy(); } 
	
	void ergodic( void (*_vis)(KEY, T) ) { _ergodic(__bst, _vis); }
	
	BSTNode<T, KEY>* getRoot() { return __bst; }
	
private:
	BSTNode<T, KEY>* __bst;
	
	void _Destroy(BSTNode<T, KEY>* &_bst)
	{
		if( _bst == NULL ) return;
		if( _bst->lc != NULL ) _Destroy(_bst->lc);
		if( _bst->rc != NULL ) _Destroy(_bst->rc);
		delete _bst;
		_bst = NULL;
	}
	
	bool _Find(BSTNode<T, KEY>* _bst, KEY key, T &val)
	{
		if( _bst == NULL ) return false;
		if( _bst->key == key )
		{
			val = _bst->data;
			return true;
		}
		if( _bst->key < key )
		{
			return _Find(_bst->rc, key, val);
		} else {
			return _Find(_bst->lc, key, val);
		}
	}
	
	int LeftRotate(BSTNode<T, KEY>* &_bst)
	{
		if( _bst == NULL || _bst->rc == NULL ) return 0;
		BSTNode<T, KEY>* _rc = _bst->rc;
		_bst->rc = _rc->lc;
		_rc->lc = _bst;
		_bst = _rc;
		return 1;
	}
	
	int RightRotate(BSTNode<T, KEY>* &_bst)
	{
		if( _bst == NULL || _bst->lc == NULL ) return 0;
		BSTNode<T, KEY>* _lc = _bst->lc;
		_bst->lc = _lc->rc;
		_lc->rc = _bst;
		_bst = _lc;
		return 1;
	}
	
	int LeftBalance(BSTNode<T, KEY>* &_bst)
	{
		if( _bst == NULL || _bst->lc == NULL ) return 0;
		BSTNode<T, KEY>* _lc = _bst->lc;
		if( _lc->bf == 1 )
		{
			_bst->bf = 0;
			_lc->bf = 0;
			RightRotate(_bst);
			return 1;
		}else if( _lc->bf == -1 )
		{
			BSTNode<T, KEY>* _rd = _lc->rc;
			if( _rd->bf == 1 )
			{
				_rd->bf = 0;
				_bst->bf = -1;
				_lc->bf = 0;
			}else if( _rd->bf == -1 )
			{
				_rd->bf = 0;
				_bst->bf = 0;
				_lc->bf = 1;
			}else{
				_rd->bf = 0;
				_bst->bf = 0;
				_lc->bf = 0;
			}
			LeftRotate(_bst->lc);
			RightRotate(_bst);
			return 1;
		}else{
			_bst->bf = -1;
			_lc->bf = 1;
			RightRotate(_bst);
			return 1;
		}
		return 0;
	}
	
	int RightBalance(BSTNode<T, KEY>* &_bst)
	{
		if( _bst == NULL || _bst->rc == NULL ) return 0;
		BSTNode<T, KEY>* _rc = _bst->rc;
		if( _rc->bf == -1 )
		{
			_bst->bf = 0;
			_rc->bf = 0;
			LeftRotate(_bst);
			return 1;
		}else if( _rc->bf == 1 )
		{
			BSTNode<T, KEY>* _ld = _rc->lc;
			if( _ld->bf == -1 )
			{
				_ld->bf = 0;
				_bst->bf = 1;
				_rc->bf = 0;
			}else if( _ld->bf == 1 )
			{
				_ld->bf = 0;
				_bst->bf = 0;
				_rc->bf = -1;
			}else{
				_ld->bf = 0;
				_bst->bf = 0;
				_rc->bf = 0;
			}
			RightRotate(_bst->rc);
			LeftRotate(_bst);
			return 1;
		}else{
			_bst->bf = -1;
			_rc->bf = 1;
			LeftRotate(_bst);
			return 1;
		}
		return 0;
	}
	
	int _Insert(BSTNode<T, KEY>* &_bst, KEY key, T val, int &taller)
	{
		if( _bst == NULL )
		{
			_bst = new BSTNode<T, KEY>;
			_bst->key = key;
			_bst->data = val;
			_bst->bf = 0;
			_bst->lc = NULL;
			_bst->rc = NULL;
			taller = 1;
			return 1;
		}
		if( _bst->key == key ) return 0;
		if( _bst->key > key )
		{
			if( !_Insert(_bst->lc, key, val, taller) ) return 0;
			if( taller )
			{
				if( _bst->bf == 1 )
				{
					LeftBalance(_bst);
					taller = 0;
					return 1;
				}else if( _bst->bf == 0 )
				{
					_bst->bf = 1;
					return 1;
				} else {
					_bst->bf = 0;
					taller = 0;
					return 1;
				}
			}
		} else {
			if( !_Insert(_bst->rc, key, val, taller) ) return 0;
			if( taller )
			{
				if( _bst->bf == -1 )
				{
					RightBalance(_bst);
					taller = 0;
					return 1;
				}else if( _bst->bf == 0 )
				{
					_bst->bf = -1;
					return 1;
				} else {
					_bst->bf = 0;
					taller = 0;
					return 1;
				}
			}
		}
		return 0;
	}
	
	int _FindMin(BSTNode<T, KEY>* &_bst, KEY &e_key, T &e_data)
	{
		if( _bst == NULL ) return 0;
		if( _bst->lc == NULL )
		{
			e_key = _bst->key;
			e_data = _bst->data;
			return 1;
		}
		
		BSTNode<T, KEY>* p = _bst->lc;
		while( p->lc != NULL )
		{
			p = p->lc;
		}
		e_key = p->key;
		e_data = p->data;
		return 1;
	}
	
	int _FindMax(BSTNode<T, KEY>* &_bst, KEY &e_key, T &e_data)
	{
		if( _bst == NULL ) return 0;
		if( _bst->rc == NULL )
		{
			e_key = _bst->key;
			e_data = _bst->data;
			return 1;
		}
		
		BSTNode<T, KEY>* p = _bst->rc;
		while( p->rc != NULL )
		{
			p = p->rc;
		}
		e_key = p->key;
		e_data = p->data;
		return 1;
	}
	
	int _Delete(BSTNode<T, KEY>* &_bst, KEY key, int &lower)
	{
		int flag = 0;
		if( _bst == NULL ) return 0;
		if( _bst->key == key )
		{
			if( _bst->lc == NULL && _bst->rc == NULL )
			{
				delete _bst;
				_bst = NULL;
				lower = 1;
				return 1;
			}else if( _bst->lc != NULL )
			{
				flag = 1;
				_FindMax(_bst->lc, _bst->key, _bst->data);
				if( !_Delete(_bst->lc, _bst->key, lower) ) return 0;
			}else{
				_bst->key = _bst->rc->key;
				_bst->data = _bst->rc->data;
				delete _bst->rc;
				_bst->rc = NULL;
				lower = 1;
				return 1;
			}
		}else if( _bst->key > key )
		{
			if( _bst->lc != NULL )
			{
				flag = 1;
				if( !_Delete(_bst->lc, key, lower) ) return 0;
			}else return 0;
		}else{
			if( _bst->rc != NULL )
			{
				flag = -1;
				if( !_Delete(_bst->rc, key, lower) ) return 0;
			}else return 0;
		}
		if( lower )
		{
			if( flag == 1 )
			{
				if( _bst->bf == 1 )
				{
					_bst->bf = 0;
					return 1;
				}else if( _bst->bf == 0 )
				{
					_bst->bf = -1;
					lower = 0;
					return 1;
				}else{
					RightBalance(_bst);
					if( _bst->bf == 0 )
						lower = 1;
					else
						lower = 0;
					return 1;
				}
			}
			if( flag == -1 )
			{
				if( _bst->bf == -1 )
				{
					_bst->bf = 0;
					return 1;
				}else if( _bst->bf == 0 )
				{
					_bst->bf = 1;
					lower = 0;
					return 1;
				}else{
					LeftBalance(_bst);
					if( _bst->bf == 0 )
						lower = 1;
					else
						lower = 0;
					return 1;
				}
			}
		}
		return 1;
	}
	
	void _ergodic(BSTNode<T, KEY>* &_bst, void (*_visit)(KEY, T) ) const
	{
		if( _bst == NULL ) return;
		if( _bst->lc != NULL ) _ergodic(_bst->lc, _visit);
		_visit(_bst->key, _bst->data);
		if( _bst->rc != NULL ) _ergodic(_bst->rc, _visit);
	}
};

#endif

