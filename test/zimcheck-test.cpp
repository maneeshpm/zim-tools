#include "gtest/gtest.h"

#include "zim/zim.h"
#include "zim/archive.h"
#include "../src/zimcheck/checks.h"


TEST(zimfilechecks, test_checksum)
{
    std::string fn = "data/zimfiles/wikibooks_be_all_nopic_2017-02.zim";

    zim::Archive archive(fn);
    ErrorLogger logger;
    
    test_checksum(archive, logger);

    ASSERT_TRUE(logger.overalStatus());
}

TEST(zimfilechecks, test_metadata)
{
    std::string fn = "data/zimfiles/wikibooks_be_all_nopic_2017-02.zim";

    zim::Archive archive(fn);
    ErrorLogger logger;
    
    test_metadata(archive, logger);

    ASSERT_TRUE(logger.overalStatus());
}

TEST(zimfilechecks, test_favicon)
{
    std::string fn = "data/zimfiles/wikibooks_be_all_nopic_2017-02.zim";

    zim::Archive archive(fn);
    ErrorLogger logger;
    
    test_favicon(archive, logger);

    ASSERT_TRUE(logger.overalStatus());
}

TEST(zimfilechecks, test_mainpage)
{
    std::string fn = "data/zimfiles/wikibooks_be_all_nopic_2017-02.zim";

    zim::Archive archive(fn);
    ErrorLogger logger;
    
    test_mainpage(archive, logger);

    ASSERT_TRUE(logger.overalStatus());
}

TEST(zimfilechecks, test_articles)
{
    std::string fn = "data/zimfiles/wikibooks_be_all_nopic_2017-02.zim";

    zim::Archive archive(fn);
    ErrorLogger logger;
    ProgressBar progress(1);

    
    test_articles(archive, logger, progress, true, true, true ,true);

    ASSERT_TRUE(logger.overalStatus());
}
