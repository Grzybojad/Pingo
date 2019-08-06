#pragma once

#include <vector>
#include <vita2d.h>

#include "texture.hpp"
#include "common.hpp"

//DEBUG
#include "gui.hpp"

// Forward declaration
class CreditsEntity;

class Credits
{
    public:
        Credits();

        void init();
        void update();
        void draw();

        bool levelHasFaded();
        bool haveEnded();

    private:
        struct CreditsElement
        {
            int position;
            CreditsEntity* entity;
        };
        std::vector<CreditsElement> elements;

        float fadePoint;
        float scrollPoint;
        
        float fadeSpeed;
        float scrollSpeed;

        int length;

        bool faded;
        bool end;
};

class CreditsEntity
{
    public:
        virtual int getHeight();
        virtual void draw( int height );

    protected:
        int height;
};

class CreditsLogo : public CreditsEntity
{
    public:
        CreditsLogo( vita2d_texture* texture );

        int getHeight() override;
        void draw( int height ) override;

    private:
        vita2d_texture* logo;
       
};

class CreditsHeader : public CreditsEntity
{
    public:
        CreditsHeader( const char* text );

        int getHeight() override;
        void draw( int height ) override;

    protected:
        const char* text;
};

class CreditsPerson : public CreditsEntity
{
    public:
        CreditsPerson( const char* displayName, const char* role );

        int getHeight() override;
        void draw( int height ) override;

    private:
        const char* displayName;
        const char* role;
};

class CreditsTextBlock : public CreditsEntity
{
    public:
        CreditsTextBlock( const char* text );

        int getHeight() override;
        void draw( int height ) override;

    protected:
        const char* text;
};