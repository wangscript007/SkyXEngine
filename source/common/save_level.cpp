
void SaveLevel(const char* name)
{
	char tmppathlevel[1024];
	sprintf(tmppathlevel, "%s%s\\%s.lvl", GData::Pathes::Levels, name, name);
	if (!Core_0FileExists(tmppathlevel))
	{

	}

	//

	sprintf(tmppathlevel, "%s%s\\%s.geom", GData::Pathes::Levels, name, name);
	SGeom_ModelsSave(tmppathlevel);

	sprintf(tmppathlevel, "%s%s\\%s.green", GData::Pathes::Levels, name, name);
	SGeom_GreenSave(tmppathlevel);
}