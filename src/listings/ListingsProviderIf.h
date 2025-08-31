#pragma once

#include <vector>

#include "Listing.h"

namespace ps
{
    class ListingsProviderIf
    {
    public:
        virtual ~ListingsProviderIf() = default;
        virtual std::vector<Listing> getListings() const = 0;
    };
}