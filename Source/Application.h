#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <vector>
#include <memory>

#include "States/StateBase.h"
#include "Renderer/RenderMaster.h"

#include "Context.h"

class Application
{
    public:
        Application(std::string&& name);

        void runLoop();

        template<typename T, typename... Args>
        void pushState(Args&&... args)
        {
            m_states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
            auto& s = m_states.back();
        }

        void popState();

    private:
        void handleEvents();

        std::vector<std::unique_ptr<StateBase>> m_states;

        Context m_context;
        RenderMaster m_masterRenderer;


        bool m_isPopState = false;
};

#endif // APPLICATION_H_INCLUDED
