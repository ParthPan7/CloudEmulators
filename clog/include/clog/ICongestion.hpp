namespace clog
{
    class ICongestion
    {
        public:
            virtual void generate();
            ~ICongestion() = default;
    };
};
