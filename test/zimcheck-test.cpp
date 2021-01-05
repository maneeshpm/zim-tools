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

    ASSERT_TRUE(logger.overallStatus());
}

TEST(zimfilechecks, test_metadata)
{
    std::string fn = "data/zimfiles/wikibooks_be_all_nopic_2017-02.zim";

    zim::Archive archive(fn);
    ErrorLogger logger;

    test_metadata(archive, logger);

    ASSERT_TRUE(logger.overallStatus());
}

TEST(zimfilechecks, test_favicon)
{
    std::string fn = "data/zimfiles/wikibooks_be_all_nopic_2017-02.zim";

    zim::Archive archive(fn);
    ErrorLogger logger;

    test_favicon(archive, logger);

    ASSERT_TRUE(logger.overallStatus());
}

TEST(zimfilechecks, test_mainpage)
{
    std::string fn = "data/zimfiles/wikibooks_be_all_nopic_2017-02.zim";

    zim::Archive archive(fn);
    ErrorLogger logger;

    test_mainpage(archive, logger);

    ASSERT_TRUE(logger.overallStatus());
}

TEST(zimfilechecks, test_articles)
{
    std::string fn = "data/zimfiles/wikibooks_be_all_nopic_2017-02.zim";

    zim::Archive archive(fn);
    ErrorLogger logger;
    ProgressBar progress(1);


    test_articles(archive, logger, progress, true, true, true ,true);

    ASSERT_TRUE(logger.overallStatus());
}

class CapturedStdout
{
  std::ostringstream buffer;
  std::streambuf* const sbuf;
public:
  CapturedStdout()
    : sbuf(std::cout.rdbuf())
  {
    std::cout.rdbuf(buffer.rdbuf());
  }

  CapturedStdout(const CapturedStdout&) = delete;

  ~CapturedStdout()
  {
    std::cout.rdbuf(sbuf);
  }

  operator std::string() const { return buffer.str(); }
};

int zimcheck (const std::vector<const char*>& args);

TEST(zimcheck, checksum_goodzimfile)
{
    CapturedStdout zimcheck_output;
    ASSERT_EQ(0, zimcheck({
      "zimcheck",
      "-C",
      "data/zimfiles/good.zim"
    }));

    ASSERT_EQ(
      "[INFO] Checking zim file data/zimfiles/good.zim" "\n"
      "[INFO] Verifying Internal Checksum..." "\n"
      "[INFO] Overall Test Status: Pass" "\n"
      "[INFO] Total time taken by zimcheck: 0 seconds." "\n"
      , std::string(zimcheck_output)
    );
}

TEST(zimcheck, nooptions_goodzimfile)
{
    CapturedStdout zimcheck_output;
    ASSERT_EQ(0, zimcheck({
      "zimcheck",
      "data/zimfiles/good.zim"
    }));

    ASSERT_EQ(
      "[INFO] Checking zim file data/zimfiles/good.zim" "\n"
      "[INFO] Verifying ZIM-archive structure integrity..." "\n"
      "[INFO] Avoiding redundant checksum test (already performed by the integrity check)." "\n"
      "[INFO] Searching for metadata entries..." "\n"
      "[INFO] Searching for Favicon..." "\n"
      "[INFO] Searching for main page..." "\n"
      "[INFO] Verifying Articles' content..." "\n"
      "[INFO] Searching for redundant articles..." "\n"
      "  Verifying Similar Articles for redundancies..." "\n"
      "[INFO] Overall Test Status: Pass" "\n"
      "[INFO] Total time taken by zimcheck: 0 seconds." "\n"
      , std::string(zimcheck_output)
    );
}

TEST(zimcheck, json_goodzimfile)
{
    CapturedStdout zimcheck_output;
    ASSERT_EQ(0, zimcheck({
      "zimcheck",
      "--json",
      "data/zimfiles/good.zim"
    }));

    ASSERT_EQ(
      "{"                                                         "\n"
      "  'zimcheck_version' : '2.1.1',"                           "\n"
      "  'file_name' : 'data/zimfiles/good.zim',"                 "\n"
      "  'file_uuid' : '00000000-0000-0000-0000-000000000000',"   "\n"
      "  'status' : true"                                         "\n"
      "}" "\n"
      , std::string(zimcheck_output)
    );
}

TEST(zimcheck, bad_checksum)
{
    CapturedStdout zimcheck_output;
    ASSERT_EQ(1, zimcheck({
      "zimcheck",
      "-C",
      "data/zimfiles/bad_checksum.zim"
    }));

    ASSERT_EQ(
      "[INFO] Checking zim file data/zimfiles/bad_checksum.zim" "\n"
      "[INFO] Verifying Internal Checksum..." "\n"
      "  [ERROR] Wrong Checksum in ZIM archive" "\n"
      "[ERROR] Invalid checksum:" "\n"
      "  ZIM Archive Checksum in archive: 00000000000000000000000000000000" "\n"
      "" "\n"
      "[INFO] Overall Test Status: Fail" "\n"
      "[INFO] Total time taken by zimcheck: 0 seconds." "\n"
      , std::string(zimcheck_output)
    );
}

TEST(zimcheck, json_bad_checksum)
{
    CapturedStdout zimcheck_output;
    ASSERT_EQ(1, zimcheck({
      "zimcheck",
      "--json",
      "-C",
      "data/zimfiles/bad_checksum.zim"
    }));

    ASSERT_EQ(
      "{"                                                         "\n"
      "  'zimcheck_version' : '2.1.1',"                           "\n"
      "  'file_name' : 'data/zimfiles/bad_checksum.zim',"         "\n"
      "  'file_uuid' : '00000000-0000-0000-0000-000000000000',"   "\n"
      "  'status' : false"                                        "\n"
      "}" "\n"
      , std::string(zimcheck_output)
    );
}
