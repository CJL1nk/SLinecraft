# SLinecraft

minecraft........ BUT WITH VEGETA AND C PLUS PLUS

Project with some of my friends and I. This will be great


# Commit Rules

### There will be more rules here as this progresses

- Ensure any code that is platform specific is encased in an #ifdef (platform). Try your best to provide preprocessor macros for both platforms but if you cannot, please mark a TODO comment above or below.
- All functions written should be modular and perform more or less a single function each. This is to ensure we can edit and swap out things like world generation functions easily without worrying of breaking other things too. Please try to stay loosely coupled and don't let it conceptually (or physically) look like [this](https://images.squarespace-cdn.com/content/v1/5bfc8dbab40b9d7dd9054f41/1554517161056-LC7DTJJLV064FPB5UF9Y/image-asset.jpeg).
- Try and keep external library usage to a minimum, and if REALLY needed, try and find a library that compiles cross-platform seamlessly. Idea here is to do (mostly) everything from scratch except the OS window drawing functions because we are NOT writing to the framebuffer.
- All functions written should be documented at the top in [Doxygen](https://www.doxygen.nl/manual/docblocks.html) style comments, above their definition in the **header files**. Ensure to provide description on what the function takes as arguments and returns.
- Please try to at least make sure the codebase compiles before pushing. This isn't REALLY necessary, but will make everyone else's lives easier for testing.