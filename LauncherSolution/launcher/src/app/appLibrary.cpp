#include "appLibrary.h"

#include "utils/utils_string.h"
#include <iostream>


std::vector<std::string> invalidPathChars = { "<", ">", "|", "\"", "?", "*", ":" };


void getFilesRecursively(std::filesystem::path searchPath, std::vector<std::filesystem::path>& outPath)
{
	for (auto const& dir_entry : std::filesystem::directory_iterator{ searchPath })
	{
		if (dir_entry.is_directory())
		{
			getFilesRecursively(dir_entry, outPath);
		}
		else
		{
			outPath.push_back(dir_entry);
		}
	}
}


AppLibrary::AppLibrary(std::filesystem::path libraryPath)
{
	std::vector<std::filesystem::path> allFiles;
	std::vector<std::filesystem::path> searchPath = { "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs",  "C:\\Users\\Colin\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs" };


	for (std::filesystem::path path : searchPath)
	{
		getFilesRecursively(path, allFiles);
	}

	for (std::filesystem::path path : allFiles)
	{
		App app;
		app.name = path.filename().string();
		app.path = path;
		m_apps[app.name] = app;
	}
}



AppLibrary::~AppLibrary()
{

}

AppLibrary::Error AppLibrary::addApp(const App& app)
{
	int errors = 0;
	if (m_apps.find(app.name) != m_apps.end())
	{
		errors |= Error::NameAlreadyExists;
	}
	if (containsOr(app.path.string(), invalidPathChars))
	{
		errors |= Error::InvalidPathChars;
	}

	if (errors != 0)
	{
		return static_cast<Error>(errors);
	}

	m_apps[app.name] = app;

	return Error::None;
}

AppLibrary::Error AppLibrary::removeApp(const std::string& name)
{
	if (m_apps.find(name) == m_apps.end())
	{
		return Error::NotFound;
	}
	m_apps.erase(name);
	return Error::None;
}

AppLibrary::Error AppLibrary::updateApp(const std::string& oldName, const App& newApp)
{ 
	int errors = 0;
	if (m_apps.find(oldName) == m_apps.end())
	{
		errors |= Error::NotFound;
	}
	if (newApp.name != oldName && m_apps.find(newApp.name) != m_apps.end())
	{
		errors |= Error::NameAlreadyExists;
	}
	if (containsOr(newApp.path.string(), invalidPathChars))
	{
		errors |= Error::InvalidPathChars;
	}

	if (errors != 0)
	{
		return static_cast<Error>(errors);
	}

	if (newApp.name == oldName)
	{
		App& oldApp = m_apps[oldName];
		oldApp.path = newApp.path;
		oldApp.description = newApp.description;
		oldApp.tags = newApp.tags;
	}
	else
	{
		m_apps.erase(oldName);
		m_apps[newApp.name] = newApp;
	}
	return Error::None;
}


AppLibrary::Error AppLibrary::isUpdateValid(const std::string& oldName, const App& newApp)
{
	int errors = 0;
	if (m_apps.find(oldName) == m_apps.end())
	{
		errors |= Error::NotFound;
	}
	if (newApp.name != oldName && m_apps.find(newApp.name) != m_apps.end())
	{
		errors |= Error::NameAlreadyExists;
	}
	if (containsOr(newApp.path.string(), invalidPathChars))
	{
		errors |= Error::InvalidPathChars;
	}

	return static_cast<Error>(errors);
}

const std::vector<App> AppLibrary::searchApps(const std::string& query)
{
	std::vector<App> result;

	for (auto const& [key, val] : m_apps)
	{
		if (contains(key, query))
		{
			result.push_back(val);
		}
	}

	return result;
}
