#include "osg/Drawable"
#include "osg/Notify"

#include "osgDB/Registry"
#include "osgDB/Input"
#include "osgDB/Output"

using namespace osg;
using namespace osgDB;

// forward declare functions to use later.
bool Drawable_readLocalData(Object& obj, Input& fr);
bool Drawable_writeLocalData(const Object& obj, Output& fw);

// register the read and write functions with the osgDB::Registry.
RegisterDotOsgWrapperProxy g_DrawableFuncProxy
(
    /*new osg::Drawable*/NULL,
    "Drawable",
    "Object Drawable",
    &Drawable_readLocalData,
    &Drawable_writeLocalData
);

bool Drawable_readLocalData(Object& obj, Input& fr)
{
    bool iteratorAdvanced = false;

    Drawable& drawable = static_cast<Drawable&>(obj);

    static ref_ptr<StateSet> s_drawstate = new osg::StateSet;
    if (StateSet* readState = static_cast<StateSet*>(fr.readObjectOfType(*s_drawstate)))
    {
        drawable.setStateSet(readState);
        iteratorAdvanced = true;
    }

    Shape* shape = static_cast<Shape *>(fr.readObjectOfType(type_wrapper<Shape>()));
    if (shape) {
      drawable.setShape(shape);
      iteratorAdvanced = true;
    }

    Drawable::UpdateCallback* uc = dynamic_cast<Drawable::UpdateCallback *>(fr.readObjectOfType(type_wrapper<Drawable::UpdateCallback>()));
    if (uc) {
      drawable.setUpdateCallback(uc);
      iteratorAdvanced = true;
    }

    Drawable::CullCallback* cc = dynamic_cast<Drawable::CullCallback *>(fr.readObjectOfType(type_wrapper<Drawable::CullCallback>()));
    if (cc) {
      drawable.setCullCallback(cc);
      iteratorAdvanced = true;
    }

    Drawable::DrawCallback* dc = dynamic_cast<Drawable::DrawCallback *>(fr.readObjectOfType(type_wrapper<Drawable::DrawCallback>()));
    if (dc) {
      drawable.setDrawCallback(dc);
      iteratorAdvanced = true;
    }

    if (fr[0].matchWord("supportsDisplayList"))
    {
        if (fr[1].matchWord("TRUE"))
        {
            drawable.setSupportsDisplayList(true);
            fr+=2;
            iteratorAdvanced = true;
        }
        else if (fr[1].matchWord("FALSE"))
        {
            drawable.setSupportsDisplayList(false);
            fr+=2;
            iteratorAdvanced = true;
        }
    }

    if (fr[0].matchWord("useDisplayList"))
    {
        if (fr[1].matchWord("TRUE"))
        {
            drawable.setUseDisplayList(true);
            fr+=2;
            iteratorAdvanced = true;
        }
        else if (fr[1].matchWord("FALSE"))
        {
            drawable.setUseDisplayList(false);
            fr+=2;
            iteratorAdvanced = true;
        }
    }
    
    if (fr[0].matchWord("useVertexBufferObjects"))
    {
        if (fr[1].matchWord("TRUE"))
        {
            drawable.setUseVertexBufferObjects(true);
            fr+=2;
            iteratorAdvanced = true;
        }
        else if (fr[1].matchWord("FALSE"))
        {
            drawable.setUseVertexBufferObjects(false);
            fr+=2;
            iteratorAdvanced = true;
        }
    }

    return iteratorAdvanced;
}


bool Drawable_writeLocalData(const Object& obj, Output& fw)
{
    const Drawable& drawable = static_cast<const Drawable&>(obj);

    if (drawable.getStateSet())
    {
        fw.writeObject(*drawable.getStateSet());
    }
    
    if (drawable.getShape())
    {
        fw.writeObject(*drawable.getShape());
    }

    if (drawable.getUpdateCallback())
    {
        fw.writeObject(*drawable.getUpdateCallback());
    }

    if (drawable.getCullCallback())
    {
        fw.writeObject(*drawable.getCullCallback());
    }

    if (drawable.getDrawCallback())
    {
        fw.writeObject(*drawable.getDrawCallback());
    }
    

    if (!drawable.getSupportsDisplayList())
    {
        fw.indent()<<"supportsDisplayList ";
        if (drawable.getSupportsDisplayList()) fw << "TRUE" << std::endl;
        else fw << "FALSE" << std::endl;
    }

    fw.indent()<<"useDisplayList ";
    if (drawable.getUseDisplayList()) fw << "TRUE" << std::endl;
    else fw << "FALSE" << std::endl;

    fw.indent()<<"useVertexBufferObjects ";
    if (drawable.getUseVertexBufferObjects()) fw << "TRUE" << std::endl;
    else fw << "FALSE" << std::endl;
    
    return true;
}
