
/*
    pbrt source code Copyright(c) 1998-2009 Matt Pharr and Greg Humphreys.

    This file is part of pbrt.

    pbrt is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.  Note that the text contents of
    the book "Physically Based Rendering" are *not* licensed under the
    GNU GPL.

    pbrt is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */

#ifndef PBRT_SAMPLERS_BESTCANDIDATE_H
#define PBRT_SAMPLERS_BESTCANDIDATE_H

// samplers/bestcandidate.h*
#include "sampler.h"
#include "paramset.h"
#include "film.h"

// BestCandidate Sampling Constants
#define SQRT_SAMPLE_TABLE_SIZE 64
#define SAMPLE_TABLE_SIZE (SQRT_SAMPLE_TABLE_SIZE * \
                           SQRT_SAMPLE_TABLE_SIZE)

// BestCandidateSampler Declarations
class BestCandidateSampler : public Sampler {
public:
    // BestCandidateSampler Public Methods
    BestCandidateSampler(int xstart, int xend, int ystart, int yend,
            int pixelSamples, float sopen, float sclose, u_long rngSeed)
        : Sampler(xstart, xend, ystart, yend, pixelSamples, sopen, sclose),
          rng(rngSeed) {
        tableWidth = (float)SQRT_SAMPLE_TABLE_SIZE / (float)sqrtf(pixelSamples);
        xTileStart = Floor2Int(xstart / tableWidth);
        xTileEnd = Floor2Int(xend / tableWidth);
        yTileStart = Floor2Int(ystart / tableWidth);
        yTileEnd = Floor2Int(yend / tableWidth);
        xTile = xTileStart;
        yTile = yTileStart;
        tableOffset = 0;
    }
    Sampler *GetSubSampler(int num, int count);
    int RoundSize(int size) const {
        return RoundUpPow2(size);
    }
    int MaximumSampleCount() { return 1; }
    int GetMoreSamples(Sample *sample);
private:
    // BestCandidateSampler Private Data
    float tableWidth;
    int tableOffset;
    int xTileStart, xTileEnd, yTileStart, yTileEnd;
    int xTile, yTile;
    RNG rng;
    static const float sampleTable[SAMPLE_TABLE_SIZE][5];
    float sampleOffsets[3];
};


BestCandidateSampler *CreateBestCandidateSampler(const ParamSet &params, const Film *film,
    const Camera *camera);

#endif // PBRT_SAMPLERS_BESTCANDIDATE_H
