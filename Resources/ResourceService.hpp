//
// Created by Richard Hodges on 14/02/2018.
//

#pragma once

#include <boost/filesystem.hpp>

struct ResourceService
{
    using path = boost::filesystem::path;


    static void deduceRoot(path program_path)
    {
        root_ = program_path.parent_path();
    }

    const path& root() const {
        return root_;
    }



    static path root_;

};

static ResourceService& resourceService()
{
    static ResourceService _;
    return _;
}

