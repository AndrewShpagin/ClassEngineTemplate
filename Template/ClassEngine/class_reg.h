
/** \mainpage ClassEngine introduction
 *
 * \section intro_sec Class Engine introduction.
 * 
 * \subsection REGISTERING Registering classes.
 * BaseClass used for serialization and UI forms designing without direct UI programming.\n
 * You should derive your class from BaseClass. Very typical example of usage:
 * \code
 * class MyClass : public BaseClass {
 * public:
 *		int x;
 *		float y;
 *		cStr s;
 *		SERIALIZE(){
 *			REG_AUTO(x);
 *			REG_AUTO(y);
 *			REG_AUTO(s);
 *		}
 * };
 * \endcode
 * 
 * You may separate registration and class definition:
 * 
 * \code
 * class MyClass : public BaseClass {
 * public:
 *		int x;
 *		float y;
 *		cStr s;
 *		SERIALIZE_LATER();
 * };
 * 
 * 
 * 
 * SERIALIZE_NOW(MyClass){
 *		REG_AUTO(x);
 *		REG_AUTO(y);
 *		REG_AUTO(s);
 * }
 * \endcode
 *
 * Class may be used for UI elements registration and for serialization, see BaseClass::Save, BaseClass::Load\n
 * In this case you may defile UI and serialization sections separately
 *
 * \code
 * class MyClass : public BaseClass{
 * public:
 *
 *		void button1();
 *		void button2();
 *		float x,y,z;
 *		
 *		SERIALIZE(){
 *			//Important! Don't use any heavy checks in this function! It is called frequently. So, use only simple checks there, no any real calculations.
 *			//If you want to create Enumerator there, use convenient _MAKE_ONCE{....} macro.
 *			{//UI registration section
 *				UI_ONLY;
 *				UI_LAYOUT("2");//two columns
 *				FUNCTION_CALL(button1);
 *				FUNCTION_CALL(button2);
 *			}
 *			{//Saving section
 *				SAVE_ONLY;
 *				REG_AUTO(x);
 *				REG_AUTO(y);
 *			}
 *			if(z>0){// you may use c++ conditions in registration section
 *				REG_AUTO(z);
 *			}
 *		}
 * };
 * \endcode
 *
 * You may register members conditionally using usual if... else ... commands.\n
 * You may use different prefixes to modify registered members. See REG_OPT, INVISIBLE, NOSAVE, RENAME, ets commands.
 *
 * \subsection USAGE Usage of the registered classes.
 * Use BaseClass::Load, BaseClass::Save, BaseClass::SaveBin, BaseClass::LoadBin to serialize.\n
 * Use BaseClass::FullCopy to copy BaseClass derived classes.\n
 * Use BaseClass::GetElement, BaseClass::FindElement to get access to class members list.\n
 * use BaseClass::reset_class to clear registered fields.\n
 *
 * \subsection COMMANDS Brief summary of commands used for registering inside SERIALIZE section
 *
 * FUNCTION_CALL(...) - register function call as button.\n
 * ICON_BUTTON/3/4(...) - add icon button.\n
 * REG_AUTO(variable) - register almost any field by default. Use REG_AUTO(variable, "new_name") to rename variable.\n
 * SLIDER(variable, ...) - int or float variable as slider in UI.\n
 * REG_TEXTURE(tex) - register integer variable as texture selection control.\n
 * FILEPATH(str) - register cStr as control to choose file path.\n
 * REG_DROPLIST(fieldID, name, EnumID) - register droplist.\n
 * MAKE_ENUMERATOR(ID,List) - create Enumerator.\n
 * BCPrintf(...) - printf - like syntax to make own dynamic custom name for the field.\n
 * See also REG_RCT(...), REG_VECTOR2D(...), REG_VECTOR3D(...), REG_VECTOR4D(...), REG_MATRIX3D(...), REG_MATRIX4D(...).\n
 * _MAKE_ONCE {...} - make some action within brackets once
 *
 * \subsection UI The UI formatting commands.
 * UI_LAYOUT(...) - define columns.\n
 *
 * \subsection MODIFIERS Modifiers before the registration of the member
 * You may use ...MODIFIERS... REG_AUTO(...) or ...MODIFIERS... FUNCTION_CALL(...) to modify how registration works.\n
 * <table>
 * <tr><th>Commans<th>Description
 * <tr><td>INVISIBLE()<td> An element which invisible in UI, but use in serialization.
 * <tr><td>READONLY()<td> An unediting element.
 * <tr><td>NOSAVE()<td> An element which visible in UI, but not use in serialization.
 * <tr><td>NORESET()<td> Element will not be initialised during reset_class
 * <tr><td>NONAME()<td> ID of the element is invisible in UI
 * <tr><td>RENAME(new_name)<td> assign other ID in UI for the control
 * <tr><td>ICON(path_to_file)<td> Insert icon if control supports. If icon is in material.io/icons/black/ then just write the icon name without extension.
 * <tr><td>CHK_GROUP(g)<td> specify group for checkbox.
 * <tr><td>APPLYSCALE()<td> apply scene scale to this control
 * <tr><td>SKIPHINT()<td> suppress hint for this element
 * <tr><td>DEFHOTKEY(combination)<td> assign default hotkey to the UI element, like HOTKEY("CTRL E")
 * <tr><td>LEFTALIGN()<td> force left-align to the control
 * </table>
 * Examples:\n
 * \code
 * void doit(int p);
 * 
 * ...
 * 
 * int x[20];
 * char c[10];
 * for(int i=0;i<10;i++){	
 *		sprintf_s<20>(c,"x%d",i);
 *		INVISIBLE RENAME(c) REG_AUTO(x[i]);//without RENAME the field will be registered as "x[i]"
 * }
 * for(int i=0;i<10;i++){	
 *		sprintf_s<20>(c,"button%d",i);
 *		RENAME(c) FUNCTION_CALL(doit, "doit", i);//register 10 buttons: button0 ... button9
 * }
 * 
 * \endcode
 *
 * \subsection NAMING Additional modifiers of fields names (partially deprecated, use modifiers whenever possible).
 * You may pass new field name using\n
 * RENAME(new_name_there) REG_AUTO(field)\n
 * or\n
 * REG_AUTO(field, new_name_there)\n
 * new_name_there may contain special characters that modify how it is shown/handled in UI. There is the list of modificators - \n
 * <table>
 * <tr><th>Value<th>Description
 * <tr><td>{0xHEXADECMAIL_VALUE} <td> set background color.
 * <tr><td>{fc0xHEXADECMAIL_VALUE} <td> set font color.
 * <tr><td>[scale=floating_value] <td> set additional scale for the field.
 * <tr><td>`intger_value <td> checkbox group identifier.
 * <tr><td>% <td> apply scene scale to this control.
 * <tr><td>{hotkey hotkey_id} <td> The hotkey will be assigned as default hotkey to the button. Like {hotkey CTRL ALT SHIFT A}
 * <tr><td># <td> don't show hint.
 * <tr><td>~ <td> The function is inaccessible in demo mode.
 * <tr><td>* <td> mandatory left align.
 * <tr><td>$ <td> don't show field name in UI.
 * <tr><td>! <td> hide field, read only.
 * <tr><td>^ <td> read only field.
 * <tr><td> {icon filename_path} <td>show icon.  If icon is in material.io/icons/black/ then just write the icon name without extension.
 * </table>
 * 
 * 
 * \section class_walking Access to the registered class members.
 *
 * Class members are actually not stored anywhere. The virtual function\n
 * BaseClass::CountObjects\n
 * used to get dynamic information about the class. But usually you should never call or create it directly.
 * This function is automatically created using SERIALISE() {...} section. You may need to override this function only if you
 * make own container for objects (like ClassArray or ClassPtr).\n
 * Usual way to walk through all members of the class looks like:\n
 * \code
 * 
 * _EACH(ClassPointer, be){//be is BaseClassElement reference
 *		//write some code there, for example seek for object that contains substring in it's name
 *		//This is actually lambda function if you will look the macro.
 *		//be is reference to BaseClassElement, you may get any ingormation about the field from there.
 *		if(be->ID.IndexOf("MySubString")!=-1){
 *			// return true means exit out of the cycle _EACH ... _EACH_END
 *			return true;
 *		}
 * } _EACH_END
 * \endcode
 *
 * You may also get element-wise access, but it is a bit slower, use it only if you don't need to walk through all memebers.\n
 *
 * \code
 * BaseClassElement be;
 * if(ClassPointer->GetElement(be, index, nullptr, nullptr)){
 *		....
 * }
 *
 * ...or use...
 * 
 * if(ClassPointer->GetElementByName("ID_of_element", nullptr, nullptr, be)){
 *		....
 * } *
 * 
 * \endcode
 * Remember that\n
 * \code
 * TimingOf(Sum_Of_All(Element_Wise_Access)) > TimingOf(Walkig_Using_EACH) > TimingOf(Single_Element_Access) > TimingOf(Walkig_Using_EACH) / Amount_of_elements
 * \endcode
 *
 * 
 * \section make_container Making own container compatible with BaseClass
 *
 * The good examples of containers are ClassArray, ClassPtr and StringsList\n
 * The key point is that you should override functions
 * \code
 *
 * virtual void CountObjects(int& required_index, int* counter, DWORD* hash, BaseClassElement* result, const std::function<bool(BaseClassElement*)>* ForEachElem, bool OnlyPointersMode) override;
 * virtual void Save(TagsList& xml, void* ClassPtr, void* Extra = NULL) override;
 * virtual bool Load(TagsList& xml,void* ClassPtr,void* Extra = NULL) override;
 * virtual void SaveBin(void* Data, void* Extra, BinStream* Out, Enumerator* ExDictionary, Enumerator* SkipList) override;
 * virtual void LoadBin(void* Data, void* Extra, BinStream* In, Enumerator* ExDictionary) override;
 * virtual	void UpdateHash(HashSummator& H, void* data = nullptr, void* extra = nullptr) override;
 * virtual int ExpandWith(const char* ElmName, void* base) override;
 * virtual bool DelElement(int index) override;
 * virtual void  reset_class(void* ptr) override;
 * virtual bool CheckDirectCasting() override;
 * virtual const char* GetClassName() override;
 *
 * Use AUTONEW() macro within the declaration scope to override new_element() and GetClassSize() automatically. 
 * \endcode
 *
 * 
 * \section DEPRECATED Deprecated commands.
 * Previously SAVE_SECTION(mask) and GetClassMask() was extensively used to mask fields. It still works, but should be replaced with realtime checks using if...else... as soon as possible.\n
 *
 */

/**
 * \file class_reg.h
 * \author Andrew Shpagin
 * \date 28 Aug 2019\n
 * \brief The document describes macro definitions used to register members using BaseClass approach.
 * \details
 */

/**
	* \brief SERIALIZE() { ... } used to register variables and functions in the class. There are no input parameters.
	* \hideinitializer
	* \details
	* Example:
	* \code
	* class MyClass : public BaseClass{
	*		int x;
	*		cStr string;
	*		void doit(int x){
	*		}
	*		static void dostatic(){
	*		
	*		}
	*		SERIALIZE(){
	*			...
	*			REG_AUTO(x, "X");//register and change name
	*			REG_AUTO(string);//register with default name
	*			CLASS_METHOD_CALL(doit, "dosomething", 1);//register method of the class
	*			if(x>3){//conditions allowed within the registration section
	*				FUNCTION_CALL(dostatic);//register static call
	*			}
	*			...
	*		}
	* };
	* \endcode
	*/
#define SERIALIZE() _DEFAULT_NEW; virtual void __COUNTOBJ override

/**
	* \brief SERIALIZE_LATER() used to register variables and functions in the class.\n
	* \hideinitializer
	* \details
	* The registration should be placed separately in cpp file using SERIALIZE_NOW(Classname) { ... } 
	*
	* Example:
	* \code
	* class MyClass : public BaseClass{
	*		int x;
	*		cStr string;
	*		void doit(int x){
	*		}
	*		static void dostatic(){
	*
	*		}
	*		SERIALIZE_LATER();
	* }
	* SERIALIZE_NOW(MyClass){
	*		REG_AUTO(x, "X");//register and change name
	*		REG_AUTO(string);//register with default name
	*		CLASS_METHOD_CALL(doit, "dosomething", 1);//register method of the class
	*		if(x>3){//conditions allowed within the registration section
	*			FUNCTION_CALL(dostatic);//register static call
	*		}
	* }
	* 
	* \endcode
	*/

#define SERIALIZE_LATER() _DEFAULT_NEW; virtual void __COUNTOBJ

/**
	* \brief SERIALIZE_NOW(classname) { ... } used to register variables and functions in the class if SERIALIZE_LATER() was declared in the class.
	* \hideinitializer
	* \param classname the name of the class to register
	* \details
	* Example:
	* \code
	* class MyClass : public BaseClass{
	*		int x;
	*		cStr string;
	*		void doit(int x){
	*		}
	*		static void dostatic(){
	*
	*		}
	*		SERIALIZE_LATER();
	* }
	* SERIALIZE_NOW(MyClass){
	*		REG_AUTO(x, "X");//register and change name
	*		REG_AUTO(string);//register with default name
	*		CLASS_METHOD_CALL(doit, "dosomething", 1);//register method of the class
	*		FUNCTION_CALL(dostatic);//register static call
	* }
	*
	* \endcode
	*/

#define SERIALIZE_NOW(x) void x::__COUNTOBJ

/**
	* \brief FUNCTION_CALL(method[,name,function_parameters]) used to register any function calls
	* \hideinitializer
	* \param method name of the function to call.\n
	* \param name Optional identifier in UI for this function.\n
	* The identifier there can't be result of calculation, you can't pass the string there, only literal identifier.\n
	* If you want to pass string as identifier use RENAME(string) FUNCTION_CALL(function);
	* \param function_parameters if function has parameters, pass it there
	* \details
	* Example:
	* \code	
	* class MyClass : public BaseClass{
	*		int MyFunction1(int x, int y){
	*			...
	*		}
	*		static void MyFunction2();
	*		SERIALIZE(){
	*			...
	*			//button in UI: PressTheButton2
	*			FUNCTION_CALL(MyFunction1,"PressTheButton2",1,2);
	*			//button in UI: MyFunction3
	*			FUNCTION_CALL(MyFunction2);
	*			...
	*		}
	*	};
	* \endcode
	*/

#define FUNCTION_CALL( ...) ARG3_CHOOSER(FUNCTION_CALL1, FUNCTION_CALL2, FUNCTION_CALL3, __VA_ARGS__);

/**
 * \brief Register function call as button.
 * \hideinitializer
 * \param icon All icons are placed in material.io/icons/black/ folder. Place new icons there, black icons on transparent 
 * \param name The hint in UIbackground. Keep material.io style.
 * \param method The function name to call
 * \details
 * Usually this method used to create bottom toolset for the class like in VoxTree, Layers, Retopo groups.\n
 * Class registration looks like:\n
 * \code
 * SERIALIZE(){
 *		//....some registrations....
 *		UI_LAYOUT("BOTTOM [][]");//add 2 buttons at the bottom of the dialog 
 *		ICON_BUTTON("add_box",AddSomething,"ADD_SOMETHING_HINT");//add something
 *		ICON_BUTTON("delete",DelSomething,"DEL_SOMETHING_HINT");//delete something
 * }
 * \endcode
 */

#define ICON_BUTTON( ... ) ARG4_CHOOSER(ICON_BUTTON2, ICON_BUTTON2, ICON_BUTTON3, ICON_BUTTON4, __VA_ARGS__);

/** 
   * \brief REG_AUTO(variable[,name]) used to register variables in the class
   * \hideinitializer
   * \param method name of the function to call
   * if you want to rename it for UI/XML add second parameter
   * \param name optional, if present, used as identifier in UI for this variable, othervice variable name used.
   * \details
   * Example:
   * \code
   * class MyClass : public BaseClass{
   *		int x;
   *		bool checkbox;
   *		cStr string;
   *		SERIALIZE(){
   *			...
   *			REG_AUTO(x, "X");
   *			REG_AUTO(checkbox);
   *			REG_AUTO(string);
   *			...
   *		}
   * };
   * \endcode
   */

#define REG_AUTO(...) REG_AUTO_MACRO_CHOOSER(__VA_ARGS__)

/**
 * \brief _EACH(bcptr, be) - Walk through class members using the macro. It is most time effective method of access to all class fields.
 * \hideinitializer
 * \param bcptr BaseClass pointer
 * \param be BaseClassElement to be referred within the cycle.
 * \details
 * \code
 * _EACH(ClassPointer, be){
 *		//write some code there, for example seek for object that contains substring in it's name
 *		//This is actually lambda function if you will look the macro.
 *		//be is reference to BaseClassElement, you may get any ingormation about the field from there.
 *		if(be->ID.IndexOf("MySubString")!=-1){
 *			// return true means exit out of the cycle _EACH ... _EACH_END
 *			return true;
 *		}
 * } _EACH_END
 * \endcode
 * 
 */
#define _EACH(bcptr, be) bcptr->ForEach([&](BaseClassElement* __bcelm)->bool { BaseClassElement& be = *__bcelm;

 /** \brief _EACH_END  - End of _EACH ... _EACH_END cycle
  * \hideinitializer
  *
  * 
  */
#define _EACH_END __bcelm->reset(); return false; } );

/** \brief _EACH_FAST_END  - In case when you don't need stringual name of member you may walk faster, in this case use _EACH ... _EACH_FAST_END cycle. 
 * \hideinitializer
 * \code
 *  BaseClass* B=nullptr;
 * _EACH(ClassPointer, be){
 *		if(be->Ptr == MyPointer){
 *			// return true means exit out of the cycle _EACH ... _EACH_FAST_END
 *			B = be->BC;//found class that corresponds to the pointer MyPointer
 *			return true;
 *		}
 * } _EACH_FAST_END
 * \endcode
 * 
 */

#define _EACH_FAST_END __bcelm->BC = nullptr; __bcelm->Ptr = nullptr; __bcelm->Visible = __bcelm->Serialize = true; return false; }, true );

 /**
  * \brief BCPrintf(...) - Use it if you want to compose name of object using printf - like syntax. Don't use sprintf directly, because
  * BCPrintf makes string only when it is required, not each time when function called.
  * \details
  * \code
  * class MyClass : public BaseClass{
  *		int Array[32];
  *		SERIALIZE(){
  *			for(int i=0;i<32;i++){
  *				REG_AUTO(Array[i],BCPrintf("A%d",i));
  *			}
  *		}
  * };
  * \endcode
  */
#define BCPrintf(...) ((ForEachElem || (result && required_index == 0)) ? comms::cStr::Format(__VA_ARGS__) : "")

/**
   *\brief DELIMITER adds the delimiter in UI
   *\hideinitializer
   *\details
   * Example:
   * \code
   * class MyClass : public BaseClass{
   *
   *		SERIALIZE(){
   *			...
   *			DELIMITER;
   *			...
   *		}
   * };
   * \endcode
   */

#define DELIMITER NOSAVE REG_AUTO_EX(GDLM, D)

/**
	*\brief REG_DROPLIST(fieldID, name, EnumID) adds the droplist to UI, list into XML. The referred variable should be int
	*\hideinitializer
	* \param fieldID - variable reference, should be int
	* \param name - name in UI/XML
	* \param EnumID - enumerator reference. Maybe identifier like "enum_name" or explicit list of items like "Item1|Item2|Item3". See example for details.
	* \details
	* Example:
	* \code
	* class MyClass : public BaseClass{
	*
	*		int x1;
	*		int x2;
	*		SERIALIZE(){
	*			...			
	*			//create enumerator just now and use immediately
	*			REG_DROPLIST(x1, "droplist1", "Item1|Item2|Item3");
	*			
	*			//Other option is to create Enumerator right there or somewhere in code
	*			_MAKE_ONCE{//use it to avoid multiple call of code
	*				Enumerator* E = ENUM.Get("MYENUMERATOR");
	*				if(E->GetAmount() == 0){
	*					E->Add("SomeItem1",Value1);
	*					E->Add("SomeItem1",Value2);
	*					...
	*				}
	*			}			
	*			REG_DROPLIST(x2, "droplist2", "MYENUMERATOR");
	*
	*			//You may define Enumerator just in one line
	*			MAKE_ENUMERATOR("MYENUMERATOR2","Item1|Item2|Item3");
	*			REG_DROPLIST(x2, "droplist2", "MYENUMERATOR2");
	*			...
	*		}
	* };
	* \endcode
	*/

#define REG_DROPLIST(fieldID, name, EnumID)	{ \
	static Enumerator* E=ENUM.Get(EnumID);\
	if(!E)E=ENUM.Create(#EnumID);\
	REG_TYPE_ANYTHING(fieldID,_index,name,E);\
}

/**
 * \brief Make Enumerator in just one line
 * \hideinitializer
 * \param name Enumerator name
 * \param content List of items "Item1,Item2,...."
 * \details
 * \code
 * MAKE_ENUMERATOR("MYENUMERATOR2","Item1|Item2|Item3");
 *
 * ....somewhere...
 * 
 * REG_DROPLIST(x2, "droplist2", "MYENUMERATOR2");
 * \endcode
 */
#define MAKE_ENUMERATOR(name, content) \
	{\
		static bool one=true;\
		if(one){\
			Enumerator* E=ENUM.Get(name);\
			StringsList L;\
			L.Split(content,"|,;\n\r");\
			for(int i=0;i<L.Count();i++)E->Add(L[i],i);\
		}\
	}

	
/**
	*\brief UI_LAYOUT(str) splits ui elements to several columns with proportional or fixed width
	*\hideinitializer
	* \param str text that defines relation between controls width. Use [value_in_pixels] to define absolute width.
	* \details
	* UI_LAYOUT may use two additional keywords: TOP and BOTTOM. TOP moves controls to the tor of the window frame (header -like)\n
	* BOTTOM moves elements to the bottom of the frame, like toolset buttons. It is recommended to use ICON_BUTTON/3/4 for bottom toolset.\n
	* Example:
	* \code
	* class MyClass : public BaseClass{
	*
	*		void button();
	*		void long_button();
	*		void X();
	*		
	*		SERIALIZE(){
	*			...
	*			//places next 3 controls in one line: [button][long_button][X], length of [button] is twice less than [long_button], [X] has fixed width 32
	*			UI_LAYOUT("1 2 [32]");
	*			CLASS_METHOD_CALL(button);//[button]
	*			CLASS_METHOD_CALL(long_button);//[long_button]
	*			CLASS_METHOD_CALL(X);//[X]			
	*			...
	*		}
	* };
	* \endcode
	*/

#define UI_LAYOUT(str) NOSAVE REG_AUTO_ANYTHING(GDLM,str);

/**
 * \brief UI_ONLY and SAVE_ONLY used if you want to register UI section and Serialization sections separately\n
 * \hideinitializer
 * \details
 * If you are using UI_ONLY or SAVE_ONLY, all commands like NOSAVE and INVISIBLE are ignored\n
 * Example:
 * \code
 * class MyClass : public BaseClass{
 *
 *		void button1();
 *		void button2();
 *		float x,y;
 *		
 *		SERIALIZE(){
 *			{//UI registration section
 *				UI_ONLY;
 *				UI_LAYOUT("2");//two columns
 *				FUNCTION_CALL(button1);
 *				FUNCTION_CALL(button2);
 *			}
 *			{//Saving section
 *				SAVE_ONLY;
 *				REG_AUTO(x);
 *				REG_AUTO(y);
 *			}
 *		}
 * };
 * \endcode
 */
#define UI_ONLY auto_keep_ex(ser,BaseClass::Serialization); auto_keep_ex(ui,BaseClass::UI_definition); BaseClass::UI_definition=true;BaseClass::Serialization=false;

/**
 * \brief SAVE_ONLY used to start serialization (only) definition section. Look UI_ONLY for details and example.
 * \hideinitializer
 * \details
 * If you are using UI_ONLY or SAVE_ONLY, all commands like NOSAVE and INVISIBLE are ignored\n
 * If you are using UI_ONLY or SAVE_ONLY, all commands like NOSAVE and INVISIBLE are ignored\n
 * Example:
 * \code
 * class MyClass : public BaseClass{
 *
 *		void button1();
 *		void button2();
 *		float x,y;
 *		
 *		SERIALIZE(){
 *			{//UI registration section
 *				UI_ONLY;
 *				UI_LAYOUT("2");//two columns
 *				FUNCTION_CALL(button1);
 *				FUNCTION_CALL(button2);
 *			}
 *			{//Saving section
 *				SAVE_ONLY;
 *				REG_AUTO(x);
 *				REG_AUTO(y);
 *			}
 *		}
 * };
 * \endcode
 */
#define SAVE_ONLY auto_keep_ex(ser,BaseClass::Serialization); auto_keep_ex(ui,BaseClass::UI_definition); BaseClass::UI_definition=false;BaseClass::Serialization=true;

 /**
  * \brief SAVE_OR_UI used to start conditional serialization or UI definition section.
  * \hideinitializer
  * \details
  * Example:
  * \code
  * class MyClass : public BaseClass{
  *
  *		void button1();
  *		void button2();
  *		float x,y;
  *		bool ui_field;
  *		bool save_fields;
  *
  *		SERIALIZE(){    
  *			{
  *				SAVE_OR_UI(save_fields,ui_field);
  *				UI_LAYOUT("2");//two columns
  *				FUNCTION_CALL(button1);
  *				FUNCTION_CALL(button2);
  *			}
  *		}
  * };
  * \endcode
  */
#define SAVE_OR_UI(save, ui) auto_keep_ex(ser,BaseClass::Serialization); auto_keep_ex(ui,BaseClass::UI_definition); BaseClass::UI_definition=ui;BaseClass::Serialization=save;
/**
	* \brief SLIDER(var,name,minvalue,maxvalue) to add integer/float slider in UI. Only float and int supported
	* \hideinitializer
	* \param var variable ref 
	* \param name name in UI
	* \param minvalue minimal value
	* \param maxvalue maximal value
	* \details
	* Example:
	* \code
	* class MyClass : public BaseClass{
	*
	*		int x;
	*		float y;
	*
	*		SERIALIZE(){
	*			...
	*			SLIDER(x,"X",0,10);
	*			SLIDER(y,"Y",0.0,10.0);
	*			...
	*		}
	* };
	* \endcode
	*/
#define SLIDER(var,name,minvalue,maxvalue) {\
	static std::tuple<BaseClass*, void*> tu = GetSliderContainer<decltype(var)>(minvalue, maxvalue);\
	if(std::get<0>(tu)){\
		REG_TYPE_GENERAL(var,std::get<0>(tu),name,std::get<1>(tu));\
	}\
}

    /**
        * \brief FSLIDER(var,name,minvalue,maxvalue,scale,inversion) to add float slider in UI. It has a bit extended syntax, allows scaling and inversion
        * \hideinitializer
        * \param var variable ref
        * \param name name in UI
        * \param minvalue minimal value
        * \param maxvalue maximal value
        * \param scale scaling value (100 if percents expected)
        * \param inversion true if value inverted, scale/value will be displayed
        * \details
        * Example:
        * \code
        * class MyClass : public BaseClass{
        *
        *		float y;
        *
        *		SERIALIZE(){
        *			...
        *			FSLIDER(y,"Y",0.0,10.0, 100, true);//100.0/y will be displayed with % sign
        *			FSLIDER(y,"YP",0.0,10.0, 100, false);//100*y% will be displayed
        *			...
        *		}
        * };
        * \endcode
        */
#define FSLIDER(var,name,minvalue,maxvalue,VisModulator,Inverse) REG_FSLIDEREX2(var,minvalue,maxvalue,minvalue,VisModulator,Inverse,name)

/**
	* \brief use FILEPATH(str, name, mask) to add file selection control in UI. Only comms::cStr supported
	* \hideinitializer
	* \param str - string variable reference
	* \param name - name in UI
	* \param mask - mask for files, like "save:*.tif;*.tiff;*.exr;*.tga;*.bmp;*.png" (save dialog) or "load:*.tif;*.tiff;*.exr;*.tga;*.bmp;*.png" (open dialog)
	* \details
	* Example:
	* \code
	* class MyClass : public BaseClass{
	*		comms::cStr path;
	*		SERIALIZE(){
	*			FILEPATH(path,"FilePath","save:*.tif;*.tiff;*.exr;*.tga;*.bmp;*.png");
	*		}
	* };
	* \endcode
	*/

#define FILEPATH(str, name, mask) REG_TYPE_ANYTHING(str,_cStr,name,(void*)mask);

/**
	* \brief use REG_TEXTURE(var[,name]) to register texture image in UI/XML
	* \hideinitializer
	* \param x - int variable reference
	* \param name - name in UI/XML, optional parameter, if not present the variable name used
	*/

#define REG_TEXTURE_2(x,y) {const char* s1=#x"";const char* s2=y"";if(s2[0])s1=s2;REG_MEMBER_EX2(_TextureID,x,s1);}
#define REG_TEXTURE_1(x) REG_TEXTURE_2(x, "")
#ifdef COMMS_WINDOWS
#define REG_TEXTURE_MACRO_CHOOSER(...)\
GET_THIRD_ARG((__VA_ARGS__, REG_TEXTURE_2, REG_TEXTURE_1))(__VA_ARGS__)
#endif // Windows
#ifdef COMMS_MACOS
#define REG_TEXTURE_MACRO_CHOOSER(...)\
GET_THIRD_ARG(__VA_ARGS__, REG_TEXTURE_2, REG_TEXTURE_1)(__VA_ARGS__)
#endif // macOS
#define REG_TEXTURE(...) REG_TEXTURE_MACRO_CHOOSER(__VA_ARGS__)

///register cVec2
#define REG_VECTOR2D(vec) {INVISIBLE REG_MEMBER(_float,vec.x);INVISIBLE REG_MEMBER(_float,vec.y);}
///register Rct
#define REG_RCT(R) {REG_MEMBER(_float,R.x);REG_MEMBER(_float,R.y);REG_MEMBER(_float,R.w);REG_MEMBER(_float,R.h);}
///register Vector3D
#define REG_VECTOR3D(vec) {INVISIBLE REG_MEMBER(_float,vec.x);INVISIBLE REG_MEMBER(_float,vec.y);INVISIBLE REG_MEMBER(_float,vec.z);}
///register Vector4D
#define REG_VECTOR4D(vec) {INVISIBLE REG_MEMBER(_float,vec.x);INVISIBLE REG_MEMBER(_float,vec.y);INVISIBLE REG_MEMBER(_float,vec.z);INVISIBLE REG_MEMBER(_float,vec.w);}
///register Matrix4D
#define REG_MATRIX4D(mat) {for(int i=0;i<4;i++)for(int j=0;j<4;j++){INVISIBLE REG_MEMBER_EX2(_float,mat.Elem(i,j),BCPrintf("%s%d%d",#mat,i,j));}}
///register Matrix3D
#define REG_MATRIX3D(mat) {for(int i=0;i<3;i++)for(int j=0;j<3;j++){INVISIBLE REG_MEMBER_EX2(_float,mat.Elem(i,j),BCPrintf("%s%d%d",#mat,i,j));}}

/**
 * \brief Don't use fields in hash calculations
 * \details
 * \code
 * int x;
 * Matrix4D M1;
 * Matrix3D M2;
 * SERIALIZE(){
 *		REG_AUTO(x);//participates in serialization
 *		NOHASH{//M1,M2 will not be hashed
 *			REG_MATRIX4D(M1);
 *			REG_MATRIX3D(M2);
 *		}
 * }
 * \endcode
 */
#define NOHASH if(!hash)

/// An element which invisible in UI, but use in serialization.
#define INVISIBLE __FIELD(Visible,false);
/// An unediting element.
#define READONLY __FIELD(ReadOnly,true);
/// An element which visible in UI, but not use in serialization.
#define NOSAVE __FIELD(Serialize,false);
/// Element will not be initialised during reset_class
#define NORESET __FIELD(Noreset,true);
/// ID of the element is invisible in UI
#define NONAME __FIELD(Noname,true);
/// assign other ID in UI for the control
#define RENAME(id) __ADDREG(cStr("[NAME ") + cStr(id) + cStr("]"));
/// Insert icon if control supports.
#define ICON(path) __ADDREG("[ICON "##path##"]");
/// specify group for checkbox.
#define CHK_GROUP(g) __ADDREG("[GROUP "#g"]");
/// apply scene scale to this control
#define APPLYSCALE __ADDREG("[APPLYSCALE]");
///suppress hint for this element
#define SKIPHINT __ADDREG("[NOHINT]");
/// assign default hotkey to the UI element, like HOTKEY("CTRL E")
#define DEFHOTKEY(combo) __ADDREG("[HOTKEY "##combo"]");
/// force left-align to the control
#define LEFTALIGN __ADDREG("[LALIGN]");
/**
Use REG_OPT to pass different settings to Class Editor. All settings should be quoted with "". We recommend using the individual defines above instead of REG_OPT for the prettiness of the code. \n
\code
REG_OPT("[NOSAVE][NONAME]") REG_MEMBER(_float, X);
\endcode

Possible options:\n
<table>
<tr><th>Value<th>Description
<tr><td>[NAME NewName] <td> assign other ID/Name for this control
<tr><td>[COLOR 0xXX...] <td> specify color for the control.
<tr><td>[FONTCOLOR 0xXX....] <td> specify font color.
<tr><td>[NOHINT] <td> don't use hint for the control.
<tr><td>[LALIGN] <td> force left align.
<tr><td>[TRIAL] <td> not allowed in trial mode.
<tr><td>[TABMASK MaskValue] <td> mask for tabs (like in settings).
<tr><td>[SPLIT] <td> insert split icon for formatting.
<tr><td>[ICON PathToIcon] <td> insert icon if control supports.
<tr><td>[HOTKEY keycombo] <td> default hotkeys combination.
<tr><td>[write something except keywords] <td> just something to make identifier unique and don't show the tag in UI.
</table>
*/
#define REG_OPT(x) __ADDREG(x);

/**
 * \brief Place 3 lines of code in correspondence with current coordinate system - Y-up or Z-up
 * \hideinitializer
 * \param x X - related item
 * \param y Y - related item
 * \param z Z - related item
 * 
 */

#define REG_COORD(x,y,z) \
	if(swYZ()){\
		z;\
		x;\
		y;\
	}else{\
		x;\
		y;\
		z;\
	}

/**
 * \brief _MAKE_ONCE - Make some action within brackets {...} once
 * \hideinitializer
 * 
 * \details
 * \code
 * _MAKE_ONCE{
 * ...do it once...
 * }
 * \endcode
 * 
 */

#define _MAKE_ONCE static bool ___LINE_NAME(b) = true; if(___ifonce(___LINE_NAME(b)))

