#pragma once
#include <filesystem>
#include <vector>
#include <string>
#include <unordered_map>



struct App;


class AppLibrary
{
public:
	enum Error;

	AppLibrary(std::filesystem::path libraryPath);
	~AppLibrary();

	AppLibrary(const AppLibrary&) = delete;
	AppLibrary(AppLibrary&&) = delete;
	AppLibrary& operator=(const AppLibrary&) = delete;
	AppLibrary& operator=(AppLibrary&&) = delete;


	Error addApp(const App& app);
	Error removeApp(const std::string& name);
	Error updateApp(const std::string& oldName, const App& newApp);
	Error isUpdateValid(const std::string& oldName, const App& newApp);

	const App* getApp(const std::string& name);
	bool hasApp(const std::string& name);
	const std::vector<App> searchApps(const std::string& query);

private:
	std::unordered_map<std::string, App> m_apps;
};



struct App
{
	std::filesystem::path path;
	std::string name;
	std::string description;
	std::vector<std::string> tags;

	std::string launchPrefix;
	std::vector<std::string> launchArgs;
};





enum AppLibrary::Error
{
	None = 0,
	NotFound = 1 << 0,
	NameAlreadyExists = 1 << 1,
	InvalidPathChars = 1 << 2,
};
