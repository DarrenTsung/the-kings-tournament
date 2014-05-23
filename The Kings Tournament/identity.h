//
//  identity.h
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#ifndef The_Kings_Tournament_identity_h
#define The_Kings_Tournament_identity_h

#include <entityx/entityx.h>

enum class EntityIdentity { PLAYER_ONE, PLAYER_TWO };

struct Identity: entityx::Component<Identity> {
    Identity(EntityIdentity identity) : identity(identity) {}
    
    EntityIdentity identity;
    
};

#endif
