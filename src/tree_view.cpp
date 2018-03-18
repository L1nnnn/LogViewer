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
#include <gtkmm/treestore.h>
#include <iostream>

#include "tree_view.hh"
#include "log_utils.hh"

TreeView::TreeView(TextView *txtView) {
    text = txtView;

    store = Gtk::TreeStore::create(record);
    this->set_model(store);

    this->load();

    this->signal_row_activated().connect(sigc::mem_fun(*this,&TreeView::on_activated));
}

void TreeView::addBaseItems(std::vector<std::string> *allItems) {
    for (int i = 0; i<allItems->size(); i++) {
        Gtk::TreeModel::Row row = *(store->append());
        row[record.col_text] = allItems->at(i);
        row[record.row_num] = 1;
    }

    this->append_column("Logs",record.col_text);
    this->show_all_children();
}

void TreeView::addToFolder(std::string folder, std::vector<std::string> *allItems) {
    Gtk::TreeModel::Children children = store->children();
    for (Gtk::TreeModel::Children::iterator iter = children.begin();
         iter!=children.end(); iter++) {
        Gtk::TreeModel::Row row = *iter;
        if (std::string(row[record.col_text])==folder) {
            for (int i = 0; i<allItems->size(); i++) {
                Gtk::TreeModel::Row sub = *(store->append(row.children()));
                sub[record.col_text] = allItems->at(i);
                sub[record.row_num] = 2;
            }
        }
    }
}

void TreeView::load() {
    auto list = LogUtils::logItems();

    std::vector<std::string> *baseItems = new std::vector<std::string>();
    for (int i = 0; i<list->size(); i++) {
        LogItem current = list->at(i);
        baseItems->push_back(current.log);
    }
    addBaseItems(baseItems);

    for (int i = 0; i<list->size(); i++) {
        LogItem current = list->at(i);
        if (current.logChildren->size()!=0) {
            addToFolder(current.log,current.logChildren);
        }
    }
}

void TreeView::on_activated(const Gtk::TreeModel::Path &path, Gtk::TreeViewColumn *col) {
    Gtk::TreeModel::iterator iter = store->get_iter(path);
    if (iter) {
        Gtk::TreeModel::Row row = *iter;
        Gtk::TreeModel::Row parent = *(row->parent());
        std::string title = "/var/log/";

        if (parent) {
            std::string parentStr = parent[record.col_text];
            title+=parentStr+"/";
        }

        if (row.children().size()>0) {
            return;
        }

        std::string childStr = row[record.col_text];
        if (childStr=="(Empty)") {
            return;
        }

        title+=childStr;
        std::cout << title << std::endl;

        std::string content = LogUtils::logContent(title);
        text->set_text(content);
    }
}
