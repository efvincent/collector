
#include <iostream>
#include <string>

#include <SDL.h>

#include <collector.h>
#include <text.h>
#include <filestore/selection.h>
#include <display/subtags.h>


Subtags::Subtags(Selection** s) : DisplayObject(s)
{

}

Subtags::~Subtags()
{
	destroy_tags();
}

void Subtags::destroy_tags()
{
	for(Text* text: tags)
		delete text;
	tags.clear();
}


void Subtags::render()
{
	//draw the background
	SDL_Rect rect = sdl->get_viewport();
	sdl->set_color(OVERLAY);
	sdl->fill_rect(rect);

	render_tags();
}

void Subtags::render_tags()
{
	SDL_Rect rect = sdl->get_viewport();

	//draw each tags text
	int x = CLI_PAD;
	for(Text* t: tags)
	{
		// std::cout << "render " << x << ", " << (rect.y + CLI_PAD) << "   " << t->get_text() << std::endl;
		t->render(x, rect.y + CLI_PAD);
		x += t->width() + (CLI_PAD * 2);
	}
}

void Subtags::on_selection()
{
	destroy_tags();

	tag_freq_vector subtags = selection()->get_subtags();

	for(tag_freq tag: subtags)
	{
		//                    [  tag  ]          [          count         ]
		std::string caption = tag.first + " (" + std::to_string(tag.second) + ")";
		Text* text = new Text(caption, config->get_color(CLI_TEXT));
		tags.push_back(text);
	}

	mark_dirty();
}