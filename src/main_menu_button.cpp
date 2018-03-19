// Copyright 2018 Patrick Flynn
//
// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, 
//	this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this 
//	list of conditions and the following disclaimer in the documentation and/or 
//	other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may 
//	be used to endorse or promote products derived from this software 
//	without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include <gtkmm/aboutdialog.h>
#include <vector>

#include "main_menu_button.hh"

//TODO: Move to separate file (such as config file)
#define VERSION "0.1"

MainMenuButton::MainMenuButton(Glib::RefPtr<Gtk::Application> appP) {
	app = appP;
	this->set_label("Menu");
	
	menu = new Gtk::Menu;
	this->set_popup(*menu);

    about = new Gtk::MenuItem;
    quit = new Gtk::MenuItem;

    about->set_label("About");
    quit->set_label("Quit");

    about->signal_activate().connect(sigc::mem_fun(*this,&MainMenuButton::on_about_clicked));
    quit->signal_activate().connect(sigc::mem_fun(*this,&MainMenuButton::on_quit_clicked));

    menu->append(*about);
    menu->append(*quit);

    menu->show_all_children();
}

void MainMenuButton::on_about_clicked() {
    Gtk::AboutDialog about;
    about.set_program_name("Log Viewer");
    about.set_version(VERSION);
    about.set_copyright("Copyright 2018 Patrick Flynn");
    about.set_logo_icon_name("logview");
    about.set_comments("A log viewing application for Linux");

    about.set_license("BSD-3 License\n\n"
                      "Redistribution and use in source and binary forms, with or without modification,\n"
                      "are permitted provided that the following conditions are met:\n"
                      " \n"
                      "1. Redistributions of source code must retain the above copyright notice,\n"
                      "	this list of conditions and the following disclaimer.\n"
                      " \n"
                      "2. Redistributions in binary form must reproduce the above copyright notice, this\n"
                      "	list of conditions and the following disclaimer in the documentation and/or\n"
                      "	other materials provided with the distribution.\n"
                      " \n"
                      "3. Neither the name of the copyright holder nor the names of its contributors may\n"
                      "	be used to endorse or promote products derived from this software\n"
                      "	without specific prior written permission.\n"
                      " \n"
                      " THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" AND\n"
                      " ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED\n"
                      " WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.\n"
                      " IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,\n"
                      " INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT\n"
                      " NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR\n"
                      " PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,\n"
                      " WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)\n"
                      " ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,\n"
                      " EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\n"
                      );
    std::vector<Glib::ustring> authors;
    authors.push_back("Patrick Flynn");
    about.set_authors(authors);

    about.run();
}

void MainMenuButton::on_quit_clicked() {
    app->quit();
}
