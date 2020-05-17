#pragma once

#include "pool.h"
#include "BaseClassIO.h"

/**
 * \file BaseClass.h
 * \author Andrew Shpagin
 * \date 28 Aug 2019\n
 * \see class_reg.h for details
 */
/**  
 * \brief BaseClassElement used to iterate over BaseClass items.\n
 * Typical pattern of usage:\n
 * \code
 *
 *_EACH(ClassPointer, be){///be is BaseClassElement reference
 *		///write some code there, for example seek for object that contains substring in it's name
 *		///This is actually lambda function if you will look the macro.
 *		///be is reference to BaseClassElement, you may get any ingormation about the field from there.
 *		if(be->ID.IndexOf("MySubString")!=-1){
 *			/// return true means exit out of the cycle _EACH ... _EACH_END
 *			return true;
 *		}
 * } _EACH_END
 * 
 * ...or...
 * 
 *  BaseClassElement be;
 *  int N=BC->GetAmountOfElements();
 *  for(int i=0;i<N;i++){
 *		if(BC->GetElement(be, i, BC, nullptr)){
 *			if(be.Visible){
 *			   //....some ui job...
 *			}
 *			if(be.Serialize){
 *			   //....some sirialization job...
 *			}
 *		}
 *	}
 * \endcode
 */
struct BaseClassElement {
	comms::cStr RegOpt;
	///pointer to exemplair
	BaseClass* BC;
	///pointer to data. If class is directly castable it is equal to BC
	void* Ptr;
	///additional methadata
	void* Extra;
	///registration name
	const char* ID;
	///usage mask
	DWORD Mask;
	///visible in UI
	bool Visible : 1;
	///Read-only marked
	bool ReadOnly : 1;
	///should be serialized
	bool Serialize : 1;
	bool ApplyScale : 1;
	bool Noname : 1;
	bool Noreset : 1;
	float Scaling;	
	///
	///for internal usage by BaseClass::GetElement(). It stores results of CONDITIONAL(...) result to avoid re-calculation on each step
	bool CachedValue : 1;
	unsigned short CachedIndex;
	///set defaults
	void fill(void* _Ptr, void* _Extra, bool _vis, bool _ui, bool OnlyPointersMode);

	void reset();
	void minimal_reset();
	BaseClassElement();
};
/**
 * \brief Use this class for build a class for UI or serialization.
 * see class_reg.h for details about the class registration
 */
class BaseClass{
protected:
	///pointer to the parent class in the tree
	BaseClass* ParentBC;
	///Result of GetClassMask() written there. GetClassMask() is not const, so can't use it in const functions. The field introduced to use masking in const functions.
	DWORD _ClassMask;
public:
	friend BaseClassElement;
	//explicit BaseClass(const BaseClass&);
	//BaseClass& operator = (const BaseClass&);
	/// BaseClass is like a tree, and you always can get the root of the tree using this function.
	BaseClass* GetRoot();
	BaseClass();
	BaseClass(const BaseClass&);
	///virtual destructor
	virtual ~BaseClass();

	/// Masking elements of class. Each member has mask. Element is serializable/visible only if (it's_mask & hosting_class_mask) != 0
	virtual DWORD GetClassMask() { return 0xFFFFFFFF; }
	DWORD& ClassMask() { return _ClassMask;	}
	
	/// Clearing all registered content of the class. If DataPtr is nullptr, this class will be cleared
	virtual void reset_class(void* DataPtr = nullptr);

	////This block of functions used for copy / serialization////
	
	/**
	 * \brief This is the main function used for the access to class members. Each class that has SERIALIZE section creates this function automatically.\n
	 * It may count members, return hash, give element-wise access to any member. Instead of keeping registered fields that routine gives fast dynamic access to any member.\n
	 * If you making own container, you should create this function as well, othervice your class will not be serialized correctly even if you will make GetElement(...) function.
	 * \param required_index Index of required element if result != nullptr
	 * \param counter if nonzero, the elements count returned there.
	 * \param hash if nonzero, returns hash value for this class.
	 * \param result if nonzero, gives access to the member with index required_index.
	 * \param ForEachElem if nonzero, the function will be called for each class element.
	 * \param OnlyPointersMode If true, the field name will not be filled for speed purposes.
	 */
	virtual void CountObjects(int& required_index, int* counter, HashSummator* hash, BaseClassElement* result, const std::function<bool(BaseClassElement*)>* ForEachElem = nullptr, bool OnlyPointersMode = false) { }

	/**
	 * \brief Calls function for each class member. This function used in _EACH ... _EACH_END cycle
	 * \param fn Function to call, usually lambda
	 * \param OnlyPointsers If true, stringual ID field of BaseClassElement will not be filled (for speed purposes).
	 */
	void ForEach(const std::function<bool(BaseClassElement* el)>& fn, bool OnlyPointsers = false);
	
	/**
	 * \brief Copy base class to other class uning names correspondence
	 * \param Dest The destination object
	 * \param Add Add members to class arrays or replace
	 * \return true if successful
	 */
	virtual     bool CopyBaseClass(BaseClass* Dest, bool Add = false);
	/**
	 * \brief Save class to the XML structure
	 * \param xml The result
	 * \param ClassPtr The pointer to the data, equals to this if class is directly castable
	 * \param Extra Extra data pointer
	 */	 
	virtual void Save(TagsList& xml, void* ClassPtr, void* Extra = NULL);
	/**
	 * \brief Load the class from the XML structure
	 * \param xml The source XML
	 * \param ClassPtr The pointer to the data, equals to this if class is directly castable
	 * \param Extra Extra data pointer
	 * \return true if successful
	 */
	virtual bool Load(TagsList& xml, void* ClassPtr, void* Extra = NULL);
	/**
	 * \brief Fast copy from one BaseClass to another. Names and types correspondence used to copy.
	 * \param SrcData Data data pointer
	 * \param SrcDataExtra Src extra
	 * \param Dest Destination class
	 * \param DestData Destination data
	 * \param DstDataExtra Destination extra
	 * \param C copy context
	 * \return true if successful
	 */
	virtual     bool FullCopy(const void* SrcData, const void* SrcDataExtra, BaseClass* Dest, void* DestData, void* DstDataExtra, CECopyContext* C);
	/**
	 * \brief Save in binaly form. Use only for temporary storage in memory!!!
	 * \param Data data pointer
	 * \param Extra extra pointer
	 * \param Out Output stream
	 * \param ExDictionary Dictionary for enumerators
	 * \param SkipList Skip list for enumerators
	 */
	virtual     void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList);
	/**
	 * \brief Load the class from the memory. Use only for temporary storage in memory!!!
	 * \param Data Pointer to the class data
	 * \param Extra Extra data
	 * \param In binary stream to read data from
	 * \param ExDictionary Additional dictionary
	 */
	virtual		void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary);
	/**
	 * \brief returns hash value dependent on data fields of this class
	 * \param data Data ptr pointer to data
	 * \param extra Extra ptr pointer to methadata
	 * \return Hash value returns some value dependent on the class inner data. Usually only serializable data influences on th return value.
	 */
	virtual void UpdateHash(HashSummator& S, void* data = nullptr, void* extra = nullptr);
	///return amount of elements represented in UI
	virtual int GetAmountOfElementsInUI();
	///return amount of elements taht will be stored in XML
	virtual int GetAmountOfElementsInXML();

	
	////This block of functions generated automatically if you are using SERIALIZE macro////
	
	///return class name there if need. Usually you don't need, if you are using AUTONEW or SERIALIZE
	virtual const char* GetClassName() const;
	///Reload this function to register members. Usually you don't need to do this if you are using any of SERIALIZE methods of registration
	virtual void RegisterMembers();
	///return complete amount of elements. Even invisible, masked and non-serialized elements will be counted
	virtual int GetAmountOfElements();

	///BaseClass corresponds to some other data type. For example _int correctonds to int, etc... In this case you can't cast pointer to data to BaseClass*.
	///But in some cases BaseClass may be directlt castable, for example if it has registered members, or it is ClassArray.
	///This function is to define if class is directly castable.
	///\return Return true if void* ClassPtr may be directly casted to BaseClass* 
	virtual bool CheckDirectCasting() const { return false; }

	///return actual size of this class
	virtual int GetClassSize() const;

	///construct pointer to class of the same type like this. Elements will not be copied into the new place
	virtual BaseClass* new_element() const;

	////end of automatically generated functions////

	////This block of functions used for the access to BaseClass elements////
	
	/**
	 * \briefThe The function returns complete information about the member by it's index. If you want to walk through all members use _EACH ... _EACH_END loop.
	 * \param res All data gathered there
	 * \param idx Index of the member
	 * \param Ptr Pointer to data (if class is direcly castable it is equal to this, othervice it points to placement of data in memory). If NULL passed, this will be used
	 * \param Extra Extra data, used for enumerators and sliders (mostly)
	 * \return return true if element exists and visible
	 */
	virtual bool GetElement(BaseClassElement& res, int idx, const void* Ptr = nullptr, const void* Extra = nullptr);
	/**
	 * \brief The function returns complete information about the member by it's name.
	 * \param Name Name of the member
	 * \param Ptr Data ptr
	 * \param Extra Extra
	 * \param res All data gathered there
	 * \return return true if element exists and visible
	 */
	bool GetElementByName(const char* Name, void* Ptr, void* Extra, BaseClassElement& res, bool UI = false, bool Serialize = true);
	bool GetElementByNameAndType(const char* Name, const char* Type, void* Ptr, void* Extra, BaseClassElement& res, bool UI = false, bool Serialize = true);

	////This block of functions used for saving data to XML in short form, skipping default fields////
	
	/// Short form saving. Fields that are unchanged in comparison to default will be skipped in XML.
	void DeleteDefaultSubFields(TagsList& xml, void* ClassPtr, void* Extra = NULL);
	///Return true if class should be saved in short form mandatory 
	virtual bool ShouldSaveInShortForm() { return false; }

	////This block of functions used for arrays to add/delete elements////
	
	///Expand array with class ElmName
	virtual int ExpandWith(const char* ElmName,void* base){	return -1; }
	///removes element if the operation supported
	virtual bool DelElement(int Index){return false;}

	//// validation of the BaseClass pointers. If you have some pointer, you may always determine if it points to any valid BaseClass exemplar ////

	///call it to check if this BaseClass pointer is valid
	template<class Type = BaseClass>
	bool valid() const;
	template<>
	bool valid<BaseClass>() const;
	///if class is directly castable the function returns ptr cased to BaseClass, othervice this pointrer returned. If NULL returned - something is wrong.
	BaseClass* auto_cast(void* ptr) const;

	/**	\brief Save the object to file or binary stream.
	* Example
	* \code
	* MyClass C;
	* MyClass C1;
	*
	* // to stream
	* MemoryBinStream BS;
	* C.ToBS(BS, true);
	* // copy from C to C1
	* C1.FromBS(BS);
	*
	* // to file
	* C.WriteToFile("file.xml");
	* C1.ReadFromFile("file.xml");
	*
	* // to string
	* cStr s;
	* C.ToStr(s);
	* C1.FromStr(s);
	* \endcode
	*/
	virtual     bool ReadFromFile    (const char* Name);
	virtual     bool WriteToFile     (const char* Name);

	virtual void ToBS(BinStream& bs, bool IncludeLength);
	virtual void FromBS(BinStream& bs);
	virtual void ToBS(BinStream& bs, void* data, void* extra, bool IncludeLength);
	virtual void FromBS(BinStream& bs, void* data, void* extra);
	virtual void ToStr(comms::cStr& bs);
	/// \see ToBS()
	virtual void FromStr(const comms::cStr& bs);
	
	
	
    /// Special function for integrating in editor.
    virtual bool CheckIfFunction() const { return false; }
    /// return -1 to do nothing, 0 if you want to hide everything after this registered member, 1 if you want to show
	virtual int			condition_call(void* ptr) { return -1; }
	
	virtual BaseClass* GetParent() const {return ParentBC;}
	template <typename type> type* FindParent();
	///set parent recursively
	virtual void SetParent(BaseClass* Parent);
	///set parent directly to this, not affecting members
	virtual void SimplySetParent(BaseClass* Parent);
	virtual bool MayBeParent() { return true; }

	/// Checking for errors of registration.
	virtual bool CheckCompartabilityWith(const char* TypeName,int TypeSize){return true;}
	
    // Editor events.
	/**
    \brief Editor will call next function always when it is visible in tree. Return true if overriden.
    */
	virtual bool ProcessInEditor(BaseClass* Parent) { return false; }
	/**
    \brief Editor will call it every time when member changes and editor is able to recognise it.
    \return The value doesn't matter.
    \see BeforeChangeMember()
    */
	virtual bool OnChangeMember(BaseClass* MembClass,void* MembPtr,void* MembExtra,const char* MembName){return false;}
    /**
    \brief Editor will call it every time before the changes.
    \see OnChangeMember()
    */
	virtual void BeforeChangeMember(BaseClass* MembClass,void* MembPtr,void* MembExtra,const char* MembName){}
	virtual int GetElementLevel(const char* EName){return 0;}
    /**
    \brief Create completely own control for ClassEditor
    \details
    Override it when need to create completely own class editor control.    
	\param[in]		FieldName is how the object registered.
	\param[out]		Rect is rectangle to place control, may be modified by this function if need.
	\param[in]		Ptr is pointer to data, if class suports direct casting it is equal to "this".
	\return			The function should return control (BaseWidget*) to place in UI
    \see One2DCurve::OnModifyControl()
    */
	virtual BaseWidget* OnCreateControlFromScratch(const ClassEditorContext& Context, Rct& Rect){ return NULL; }
	/**
	\brief Call for every member of registered class registered class.
	\details
	Override it when you need to modify default class editor control. This routine allows to modify class editor controls without rewriting from scratch.
	Build controls in the `W`.
	\see MultiMtlLayer::OnModifyControl()
	\see RetopoGroup::OnModifyControl()
	\see VoxTreeBranch::OnModifyControl()
	*/
	virtual void OnModifyControl(const char* FieldName, BaseWidget* W, ClassEditorContext& Context){};

    /**
    \brief Use it for build a Drag & Drop element.
    \see CanAcceptDrag(), OnStartDrag(), OnEndDrag(), OnAcceptDrag()
    */
	virtual bool CanBeDragged(const char* MemberID,int& dx,int& dy){return false;}
    /// \see CanBeDragged(), OnStartDrag(), OnEndDrag(), OnAcceptDrag()
	virtual bool CanAcceptDrag(const char* MemberID){return false;}
    /// \see CanBeDragged(), CanAcceptDrag(), OnEndDrag(), OnAcceptDrag()
    virtual bool OnStartDrag( const char* MemberID ){ return false; }
    /// \see CanBeDragged(), CanAcceptDrag(), OnStartDrag(), OnAcceptDrag()
    virtual bool OnEndDrag( const char* MemberID ){ return false; }
    /// \see CanBeDragged(), CanAcceptDrag(), OnStartDrag(), OnEndDrag()
    virtual bool OnAcceptDrag( BaseClass* DraggedItemParent, const char* DraggedMemberID, const char* AcceptorMemberID, iRct MyRect ){ return false; }
	virtual bool UsePointerInHashCalculation() { return false; }
	virtual bool SkipHash(){return false;}

	virtual const char* GetCmdID(){return NULL;}
	///set parents to this for all child members
	void SetParents();

	static const char* GetCurrentSaveFile();
	
	/// If user triggers saving class to file, last filename stored there
	static const char* CurrentSaveFile;

	virtual void UpdateClassMembersAndMask( bool recursive );
	
	static bool SaveInShortForm;

protected:
	static bool UI_definition;
	static bool Serialization;
protected:
	
	///mutex for register_this / remove_this
	static std::mutex* pmutex;
	///each BaseClass registered in this list
	static uni_hash<_empty, cPtrDiff, (1 << 18), 2048> * presence;
	void register_this();
	void remove_this();
};

inline void HashSummator::operator+=(BaseClass* value) {
	if(value)value->UpdateHash(*this);
}