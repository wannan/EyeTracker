#include "Browser.h"
#include "MainLoopRunner.h"
#include "Tracker.h"
#include <iostream>
#include <iomanip>
#include <boost/program_options.hpp>
#include <boost/thread.hpp>
#include <tobii/sdk/cpp/EyeTrackerBrowser.hpp>
#include <tobii/sdk/cpp/EyeTrackerBrowserFactory.hpp>
#include <tobii/sdk/cpp/EyeTrackerInfo.hpp>
#include <tobii/sdk/cpp/EyeTracker.hpp>
#include <tobii/sdk/cpp/UpgradePackage.hpp>
#include <tobii/sdk/cpp/SyncManager.hpp>

using ::std::string;
using ::std::cout;
using ::std::cerr;
using ::std::endl;
using ::std::ostream;

namespace options = boost::program_options;

using namespace tetio;

static const char tab = '\t';

Browser::Browser() :
trackerId_(""),
trackerFound_(false)
{
}

void Browser::listEyeTrackers()
{
	cout << "Browsing for Eye Trackers..." << endl;
	MainLoopRunner runner;
	runner.start();
	EyeTrackerBrowser::pointer_t browser(EyeTrackerBrowserFactory::createBrowser(runner.getMainLoop()));
	browser->addEventListener(boost::bind(&Browser::onEyeTrackerBrowserEventList, this, _1, _2));
	startEyeTrackerLookUp(browser, "Browsing for eye trackers, please wait ...");
}

void Browser::printEyeTrackerInfo(std::string& trackerId)
{
	cout << "Printing info about Eye Tracker: " << trackerId << endl;
	trackerId_ = trackerId;
	trackerFound_ = false;

	MainLoopRunner runner;
	runner.start();
	EyeTrackerBrowser::pointer_t browser(EyeTrackerBrowserFactory::createBrowser(runner.getMainLoop()));
	browser->addEventListener(boost::bind(&Browser::onEyeTrackerBrowserEventPrintInfo, this, _1, _2));
	startEyeTrackerLookUp(browser, "Browsing for " + trackerId + ", please wait ...");

	if (!trackerFound_)
	{
		cout << "Could not find any tracker with name: " << trackerId_ << endl;
	}
}

void Browser::onEyeTrackerBrowserEventList(EyeTrackerBrowser::event_type_t type, EyeTrackerInfo::pointer_t info)
{
	if (type == EyeTrackerBrowser::TRACKER_FOUND) {
		cout
			<< std::setw(18) << std::left << info->getProductId() << tab
			<< std::setw(5) << std::left << info->getStatus() << tab
			<< std::setw(5) << std::left << info->getGeneration() << tab
			<< std::setw(13) << std::left << info->getModel() << tab
			<< std::setw(15) << std::left << info->getGivenName() << tab
			<< info->getVersion()
			<< endl;
	}
}

void Browser::onEyeTrackerBrowserEventPrintInfo(EyeTrackerBrowser::event_type_t type, EyeTrackerInfo::pointer_t info)
{
	if (type == EyeTrackerBrowser::TRACKER_FOUND && info->getProductId() == trackerId_)
	{
		trackerFound_ = true;

		cout
			<< "Product ID: " << info->getProductId() << endl
			<< "Given name: " << info->getGivenName() << endl
			<< "Model:      " << info->getModel() << endl
			<< "Version:    " << info->getVersion() << endl
			<< "Status:     " << info->getStatus() << endl;
	}
}

void startEyeTrackerLookUp(EyeTrackerBrowser::pointer_t browser, std::string browsingMessage)
{
	browser->start();
	// wait for eye trackers to respond.
#ifdef __APPLE__
	// Slight different bonjuor behaviour on Mac vs Linux/Windows, ... On MAC this needs to be > 30 seconds
	cout << browsingMessage << endl;
	boost::this_thread::sleep(boost::posix_time::milliseconds(60000));
#else		
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
#endif
	browser->stop(); // NOTE this is a blocking operation.
}

Tracker* Browser::getTracker() {

	Tracker *tracker = new Tracker(info);
	return tracker;
}

