/*
 * Xournal++
 *
 * Handler for layer selection and hiding / showing layer
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#pragma once

#include <optional>
#include <string>
#include <vector>

#include "control/Actions.h"
#include "gui/dialog/RenameLayerDialog.h"
#include "model/DocumentListener.h"
#include "model/PageRef.h"


class LayerCtrlListener;
class Control;
class Layer;

class LayerController: public DocumentListener {
public:
    LayerController(Control* control);
    ~LayerController() override = default;

public:
    void documentChanged(DocumentChangeType type) override;
    void pageSelected(size_t page) override;

public:
    void insertLayer(PageRef page, Layer* layer, Layer::Index layerPos);
    void removeLayer(PageRef page, Layer* layer);

    // Listener handling
public:
    void addListener(LayerCtrlListener* listener);
    void removeListener(LayerCtrlListener* listener);
    void fireRebuildLayerMenu();

protected:
    void fireLayerVisibilityChanged();

public:
    bool actionPerformed(ActionType type);

    /**
     * Show all layer on the current page
     */
    void showAllLayer();

    /**
     * Hide all layer on the current page
     */
    void hideAllLayer();

    /**
     * Show / Hide all layer on the current page
     */
    void hideOrHideAllLayer(bool show);

    void addNewLayer();
    void deleteCurrentLayer();
    void copyCurrentLayer();
    void moveCurrentLayer(bool up);
    void mergeCurrentLayerDown();
    void switchToLay(Layer::Index layerId, bool hideShow = false);
    void setLayerVisible(Layer::Index layerId, bool visible);

    PageRef getCurrentPage() const;
    size_t getCurrentPageId() const;

    /**
     * @return Layer count of the current page
     */
    Layer::Index getLayerCount() const;

    /**
     * @return Current layer ID
     */
    Layer::Index getCurrentLayerId() const;

    /**
     * @return Current layer name
     */
    std::string getCurrentLayerName() const;

    /**
     * @return Get layer name by layer id
     */
    std::string getLayerNameById(Layer::Index id) const;

    /**
     * Sets current layer name
     */
    void setCurrentLayerName(const std::string& newName);

    /**
     * Make sure there is at least one layer on the page
     */
    void ensureLayerExists(PageRef page);

private:
    Control* control;

    std::list<LayerCtrlListener*> listener;

    size_t selectedPage;

    friend class LayerRenameUndoAction;
};