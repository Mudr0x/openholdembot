#include "PlayerModel.h"
#include <assert.h>


namespace G5Decision
{
    ActionDistribution PlayerModel::getAD(const PreFlopParams& preFlopParams) const
    {
        return preFlopAD[preFlopParams.toIndex()];
    }
    
    ActionDistribution PlayerModel::getAD(const PostFlopParams& postFlopParams) const
    {
        return postFlopAD[postFlopParams.toIndex()];
    }
}
