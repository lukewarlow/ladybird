/*
 * Copyright (c) 2020, the SerenityOS developers.
 * Copyright (c) 2024, Sam Atkins <sam@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Forward.h>
#include <LibWeb/ARIA/Roles.h>
#include <LibWeb/HTML/HTMLElement.h>
#include <LibWeb/HTML/ToggleTaskTracker.h>

namespace Web::HTML {

class HTMLDialogElement final : public HTMLElement {
    WEB_PLATFORM_OBJECT(HTMLDialogElement, HTMLElement);
    GC_DECLARE_ALLOCATOR(HTMLDialogElement);

public:
    virtual ~HTMLDialogElement() override;

    virtual void removed_from(Node* old_parent, Node& old_root) override;

    String return_value() const;
    void set_return_value(String);

    String closed_by() const;
    WebIDL::ExceptionOr<void> set_closed_by(String);

    WebIDL::ExceptionOr<void> show();
    WebIDL::ExceptionOr<void> show_modal();
    void close(Optional<String> return_value);
    void request_close(Optional<String> return_value);

    // https://www.w3.org/TR/html-aria/#el-dialog
    virtual Optional<ARIA::Role> default_role() const override { return ARIA::Role::dialog; }

    bool is_modal() const { return m_is_modal; }

private:
    HTMLDialogElement(DOM::Document&, DOM::QualifiedName);

    virtual void initialize(JS::Realm&) override;
    virtual void visit_edges(Cell::Visitor&) override;

    // ^DOM::Element
    virtual void attribute_changed(FlyString const& name, Optional<String> const& old_value, Optional<String> const& value, Optional<FlyString> const& namespace_) override;

    void queue_a_dialog_toggle_event_task(String old_state, String new_state);

    void close_the_dialog(Optional<String> result);

    void run_dialog_focusing_steps();

    void set_close_watcher();

    String m_return_value;
    bool m_is_modal { false };
    Optional<String> m_request_close_return_value;
    GC::Ptr<CloseWatcher> m_close_watcher;

    // https://html.spec.whatwg.org/multipage/interactive-elements.html#dialog-toggle-task-tracker
    Optional<ToggleTaskTracker> m_dialog_toggle_task_tracker;
};

}
