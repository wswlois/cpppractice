#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>

int main(int argc, char* argv[])
{
	std::string initFileName = "log4cpp.properties";
	log4cpp::PropertyConfigurator::configure(initFileName);

	log4cpp::Category& root = log4cpp::Category::getRoot();

	root.warn("Storm is coming");

	root.debug("Received storm warning");
	root.info("Closing all hatches");

	root.debug("Hiding solar panels");
	root.error("Solar panels are blocked");
	root.debug("Applying protective shield");
	root.warn("Unfolding protective shield");
	root.info("Solar panels are shielded");

	root.info("All hatches closed");

	root.info("Ready for storm.");

	log4cpp::Category::shutdown();

	return 0;
}
